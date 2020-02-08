#include "../Message/ATM_message.cpp"

class atm{
    messaging::receiver incoming;
    messaging::sender bank;
    messaging::sender interface_hardware;

    void(atm::*state)();        // state 是一个 void 类型的函数指针

    std::string account;
    unsigned withdrawal_amount;
    std::string pin;

    void process_withdrawal(){
        incoming.wait().
        handle<withdraw_ok>(
            [&](withdraw_ok const& msg){
                interface_hardware.send(issue_money(withdrawal_amount));
                bank.send(withdrawal_processed(account, withdrawal_amount));

                state = &atm::done_processing;
            }
        ).handle<withdraw_denied>(
            [&](withdraw_denied const& msg){
                interface_hardware.send(display_insufficient_funds());

                state = &atm::done_processing;
            }
        ).handle<cancel_pressed>(
            [&](cancel_pressed const& msg){
                bank.send(cancel_withdrawal(account, withdrawal_amount));
                interface_hardware.send(display_withdrawal_cancelled());

                state = &atm::done_processing;
            }
        );
    }

    void process_balance(){
        incoming.wait().
        handle<balance>(
            [&](balance const& msg){
                interface_hardware.send(display_balance(msg.amount));

                state = &atm::wait_for_action;
            }
        ).handle<cancel_pressed>(
            [&](cancel_pressed const& msg){
                state = &atm::done_processing;
            }
        );
    }

    void wait_for_action(){
        interface_hardware.send(display_withdrawal_options());

        incoming.wait()
        .handle<withdraw_pressed>(
            [&](withdraw_pressed const& msg){
                withdrawal_amount = msg.amount;
                bank.send(withdraw(account, msg.amount, incoming));
                
                state = &atm::process_withdrawal;
            }
        ).handle<balance_pressed>(
            [&](balance_pressed const& msg){
                bank.send(get_balance(account, incoming));
                
                state = &atm::process_balance;
            }
        ).handle<cancel_pressed>(
            [&](cancel_pressed const& msg){
                state = &atm::done_processing;
            }
        );
    }

    void verifying_pin(){
        incoming.wait()
        .handle<pin_verified>(
            [&](pin_verified const& msg){
                state = &atm::wait_for_action;
            }
        ).handle<pin_incorrect>(
            [&](pin_incorrect const& msg){
                interface_hardware.send(display_pin_incorrect_message());
                
                state = &atm::done_processing;
            }
        ).handle<cancel_pressed>(
            [&](cancel_pressed const& msg){
                state = &atm::done_processing;
            }
        );
    }

    void getting_pin(){
        incoming.wait()
        .handle<digit_pressed>(
            [&](digit_pressed const& msg){
                pin += msg.digit;
                if(pin.length() == 4){
                    bank.send(verify_pin(account, pin, incoming));

                    state = &atm::verifying_pin;
                }
            }
        ).handle<clear_last_pressed>(
            [&](clear_last_pressed const& msg){
                if(!pin.empty())
                    pin.pop_back();
            }
        ).handle<cancel_pressed>(
            [&](cancel_pressed const& msg){
                state = &atm::done_processing;
            }
        );
    }

    void waiting_for_card(){
        interface_hardware.send(display_enter_card());

        incoming.wait()
        .handle<card_inserted>(
            [&](card_inserted const& msg){
                account = msg.account;
                pin = "";
                interface_hardware.send(display_enter_pin());
                state = &atm::getting_pin;
            }
        );
    }

    void done_processing(){
        interface_hardware.send(eject_card());
        state = &atm::waiting_for_card;
    }

    atm(atm const&) = delete;
    atm& operator=(atm const&) = delete;

public:
    atm(messaging::sender _bank, messaging::sender _interface_hardware)
        : bank(_bank), interface_hardware(_interface_hardware) {}

    void done(){
        get_sender().send(messaging::close_queue());
    }

    void run(){
        state = &atm::waiting_for_card;
        try{
            while(1)
                (this->*state)();
        }catch(messaging::close_queue const&){

        }
    }

    messaging::sender get_sender(){
        return incoming;
    }
};


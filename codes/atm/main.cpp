#include <thread>
#include "FST/ATM_FST.cpp"
#include "FST/Bank_FST.cpp"
#include "FST/User_FST.cpp"

int main(){
    bank_machine bank;
    interface_machine interface_hardware;

    atm machine(bank.get_sender(), interface_hardware.get_sender());

    std::thread bank_thread(&bank_machine::run, &bank);
    std::thread if_thread(&interface_machine::run, &interface_hardware);
    std::thread atm_thread(&atm::run, &machine);

    messaging::sender atm_queue(machine.get_sender());

    bool quit_pressed = false;

    while(!quit_pressed){
        char c = getchar();
        switch (c)
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            atm_queue.send(digit_pressed(c));
            break;
        
        case 'b':
            atm_queue.send(balance_pressed());
            break;
        case 'w':
            atm_queue.send(withdraw_pressed(50));
            break;
        case 'c':
            atm_queue.send(cancel_pressed());
            break;
        case 'q':
            quit_pressed = true;
            break;
        case 'i':
            atm_queue.send(card_inserted("acc1234"));
            break;

        default:
            break;
        }
    }

    bank.done();
    machine.done();
    interface_hardware.done();

    atm_thread.join();
    bank_thread.join();
    if_thread.join();

    // std::cout << "build successed" << std::endl;

    return 0;
}
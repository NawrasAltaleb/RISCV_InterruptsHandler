//
// Created by Nawras Altaleb (nawras.altaleb89@gmail.com) on 11/22/18.
//

#ifndef PROJECT_PLIC_GATEWAY_H
#define PROJECT_PLIC_GATEWAY_H

// Adjusts code to be appropriate for the SCAM tool
// Working ESL-Description -> #define NOSCAM
// Properties can be generated -> //#define NOSCAM
#define NOSCAM

#include "systemc.h"
#include "Interfaces.h"

class Gateway_PPA : public sc_module {
public:

    //Constructor
    SC_HAS_PROCESS(Gateway_PPA);

    Gateway_PPA(sc_module_name name) :
            IntSig("IntSig"),
            IntReq("IntReq"),
            fromMemoryPending("fromMemoryPending"),
            int_data(false),
            claimed_data(false),
            int_counter(0),
            int_allowed(true),
            comm_status(false)
    {
        SC_THREAD(run);
    }

    slave_in<bool> IntSig;
    master_out<bool> IntReq;
    slave_in<bool> fromMemoryPending;

    bool int_data;
    bool claimed_data;

    int int_counter;
    bool int_allowed;

    bool comm_status;

    void run(){
        while(true){

            if((int_counter > 0) && int_allowed){
                int_allowed = false;
                IntReq->write(true);
            }

            comm_status = fromMemoryPending->nb_read(claimed_data);
            if(comm_status && claimed_data){
                int_allowed = true;
                if(int_counter > 0)
                    int_counter = int_counter - 1;
            }

            comm_status = IntSig->nb_read(int_data);
            if(comm_status && int_data){
                int_counter = int_counter + 1;
            }

        }
    }
};

#ifndef NOSCAM

class Gateway_level : public sc_module {
public:

    //Constructor
    SC_HAS_PROCESS(Gateway_level);

    Gateway_level(sc_module_name name) :
            IntSig("IntSig"),
            IntReq("IntReq"),
            fromMemoryPending("fromMemoryPending"),
            int_data(SC_LOGIC_0),
            int_counter(0),
            int_pending(false),
            comm_status(false)
    {
        SC_METHOD(Process_Int);
        sensitive << IntSig;

        SC_THREAD(run);
    }

    sc_in<sc_logic> IntSig;
    master_out<bool> IntReq;
    slave_in<bool> fromMemoryPending;

    sc_logic int_data;
    unsigned int int_counter;
    bool int_pending;

    void Process_Int() {
        int_data = IntSig->read();
        if(int_data == SC_LOGIC_1) /// level interrupt
            int_counter++;
    }

    bool comm_status;

    void run(){
        while(true){

            comm_status = fromMemoryPending->nb_read(int_pending);

            if(comm_status && int_pending){
                if(int_counter > 0)
                    int_counter--;
            }

            if((int_counter > 0) && int_pending)
                IntReq->write(true);
        }
    }
};

#endif

#endif //PROJECT_PLIC_GATEWAY_H

//
// Created by Nawras Altaleb (nawras.altaleb89@gmail.com) on 20.3.18..
//

#include <iostream>

#include "Core_test.h"


int sc_main(int argc, char *argv[]) {
    if (argc == 2) {
        Core_test *test_object = new Core_test(argc, argv);
        test_object->perform_test();
        return 0;
    } else {
        std::cout << "You must specify the elf file path as the first argument Terminating..." << endl;
        return 1;
    }
}
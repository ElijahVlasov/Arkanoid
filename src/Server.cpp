#include <cstdlib>

#include <iostream>

#include <boost/program_options.hpp>

using namespace std;

using namespace boost::program_options;



Server::Server(int argc, char* argv[]) {

    if(argc < 2) {

        cerr << "Необходимы аргументы" << endl;

        exit(EXIT_FAILURE);

    }

    options_description desc("Опции сервера");

    desc.add_options()
            ("help,h",      "Справка")
            ("port,p",      "TCP-порт")
            ("config,c"     "Конфигурационный файл")

    variables_map vm;

    store(parse_command_line(argc, argv, desc), vm);

}



Server::~Server() {

    

}



int Server::run() {

    return EXIT_SUCCESS;

}

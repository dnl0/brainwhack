#include <brainwhack.hpp>

auto main(int argc, char** argv) -> int {
    options_ options = parse_options(std::vector <std::string> {argv+1, argv+argc});

    if (options.empty) {
        main_::process_issue(main_::no_file_);
    }
    if (!options.unknown.empty()) {
        main_::process_issue(main_::unknown_options_, options.unknown);
    }
    if (options.print_help) {
        print_help();
        exit(EXIT_SUCCESS);
    }
    if (options.filename.empty()) {
        main_::process_issue(main_::no_file_);
    }

    std::string buffer = file_to_string(options.filename);

    if (options.do_codegen) {
        auto ccode = codegen(parse(lex(buffer)));
        string_to_c_file(ccode, options.filename);
        exit(EXIT_SUCCESS);
    }

    interpret(parse(lex(buffer)));
}

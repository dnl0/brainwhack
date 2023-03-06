#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

#include <brainwhack.hpp>

options_ parse_options(std::vector <std::string> options)
{
    options_ result {};
    result.empty = !(options.size());

    for (auto& x: options) {
        if (!(x.compare("--help"))) {
            result.print_help = true;
            return result; // other flags don't matter, only help will be output
        }
        else if (!(x.compare("--codegen"))) {
            result.do_codegen = true;
        }
        else if (x.find_last_of(".bf") != std::string::npos) {
            result.filename = x;
        }
        else {
            result.unknown += x;
        }
    }

    return result;
}

void print_help()
{
    std::cout << "brainwhack [--flags] [.bf file]\n" <<
                 "\n" <<
                 "--help                display this message\n" <<
                 "--codegen             generate C code out of BF file\n" <<
                 "\n" <<
                 "for bug report please go to the github repository at dnl/brainwhack\n";
}

std::string bf_to_c_filename(std::string& filename)
{
    filename[filename.size()-2] = 'c';  // <name>.bf -> <name>.cf
    filename.pop_back();                // <name>.cf -> <name>.c
    return filename;
}

std::string file_to_string(const std::string& filename)
{
    std::ifstream ifile {filename, ifile.in };
    if (!ifile) { main_::process_issue(main_::file_not_found_, filename); }

    std::stringstream stream_buffer;
    stream_buffer << ifile.rdbuf();
    ifile.close();

    std::string buffer = stream_buffer.str(); 
    return buffer;
}

void string_to_c_file(const std::string& source, std::string filename)
{
    std::ofstream ofile {bf_to_c_filename(filename)};
    if (!ofile) { main_::process_issue(main_::cant_create_c_file_); }

    ofile << source;
    ofile.close();
}

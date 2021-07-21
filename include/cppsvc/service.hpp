module;

#include <string>
#include <memory>
#include <vector>
#include <functional>

#include <lingo/string.hpp>

#ifdef _WIN32
#include <windows.h>
#endif _WIN32

export module service;

namespace elisauder::cppsvc {

    export class service_base {
    
    private:

        SERVICE_STATUS _status = { 0 };
        SERVICE_STATUS_HANDLE _status_handle = NULL;

        HANDLE _service_stop_event = INVALID_HANDLE_VALUE;

        void __stdcall service_main(unsigned long argc, wchar_t* argv);
        void __stdcall service_ctrl_handler(unsigned long);
        unsigned long __stdcall service_worker_thread(void* lp_param); 

        SERVICE_TABLE_ENTRY service_table[2];

        std::wstring _service_name;

        friend void __stdcall service_main_test(unsigned long argc, wchar_t* argv);


    public:

        service_base(std::wstring service_name) : _service_name{service_name} {

            //void (__stdcall *function_ptr)(unsigned long argc, wchar_t* argv) {&service_base::service_main_test}

        }

    private:

        VOID WINAPI ServiceMain(DWORD argc, LPTSTR* argv) {

            DWORD status = E_FAIL;



        }

    };

    export class service_manager {
    private:

        static std::unordered_map<std::string, elisauder::cppsvc::service_base> service_table;

        static VOID WINAPI windows_service_main(DWORD argc, LPTSTR* argv) {
            
            LPTSTR service_name;

            if (argc >= 1) {
                service_name = *(argv + 1);
            }
            else {
                //throw std::exception("No arguments provided from windows to main service function.");
            }

        }

    };

}
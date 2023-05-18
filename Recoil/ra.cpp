#include "ra.h"



void ra::f1_r04256()
{
    while (true)
    {
        try
        {
           
            globals::rust = FindWindow(0, skCrypt(L"Rust"));

            RECT rect;

            if (globals::rust && GetWindowRect(globals::rust, &rect))
            {
                int width = rect.right - rect.left;
                int height = rect.bottom - rect.top;

                if (height > 720)
                {

                    break;
                }
            }
            
        }

        catch (std::exception e) {
            utils::echo_error(e, 0x07);
        }
        Sleep(2000);

    }
}
int ra::nral()
{
    LI_FN(srand)(time(0));

    int t103251 = 0;

    for (int x = 0; x < 30; x++)
    {
        t103251 = rand();
    }

    return t103251;
}

std::string ra::nsal()
{
    std::string alphabet = XorStr("abcdefghijklmnopqrstuvwxyz");
    std::string lol = XorStr(" ");
    LI_FN(srand)(time(0));
    for (int i = 0; i < 26; i++)
    {
        lol = lol + alphabet[rand() % 26];
    }
   
    return lol;
}
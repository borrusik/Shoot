#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace ShootingTargetsApp;

[STAThread]
int main(array<String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    MyForm form;
    Application::Run(%form);
    return 0;
}

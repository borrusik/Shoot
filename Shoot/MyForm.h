#pragma once

#include "Game.h"

namespace ShootingTargetsApp {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        MyForm(void)
        {
            InitializeComponent();

            game = new Game();
            game->Start(this->ClientSize.Width, this->ClientSize.Height);

            timer = gcnew System::Windows::Forms::Timer();
            timer->Interval = 33;
            timer->Tick += gcnew System::EventHandler(this, &MyForm::OnTimerTick);
            timer->Start();
        }

    protected:
        ~MyForm()
        {
            if (components)
                delete components;
            if (game != nullptr) {
                delete game;
                game = nullptr;
            }
        }

    private:
        Game* game;
        System::Windows::Forms::Timer^ timer;
        System::Windows::Forms::Button^ btnRestart;
        System::ComponentModel::Container^ components;

#pragma region Design 
        void InitializeComponent(void)
        {
            this->btnRestart = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();
         
            this->btnRestart->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)), static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
            this->btnRestart->FlatAppearance->BorderSize = 0;
            this->btnRestart->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(130)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
            this->btnRestart->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(70)), static_cast<System::Int32>(static_cast<System::Byte>(170)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
            this->btnRestart->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnRestart->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
            this->btnRestart->ForeColor = System::Drawing::Color::White;
            this->btnRestart->Location = System::Drawing::Point(0, 0);
            this->btnRestart->Name = L"btnRestart";
            this->btnRestart->Size = System::Drawing::Size(180, 55);
            this->btnRestart->TabIndex = 0;
            this->btnRestart->Text = L"Рестарт";
            this->btnRestart->UseVisualStyleBackColor = false;
            this->btnRestart->Visible = false;
            this->btnRestart->Click += gcnew System::EventHandler(this, &MyForm::OnRestartClick);

            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::White;
            this->ClientSize = System::Drawing::Size(600, 400);
            this->Controls->Add(this->btnRestart);
            this->DoubleBuffered = true;
            this->Name = L"MyForm";
            this->Text = L"Стрільба по мішеням";
            this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
            this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseDown);
            this->ResumeLayout(false);

        }
#pragma endregion

    private:
        System::Void MyForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
        {
            game->Draw(e->Graphics);

            Drawing::Font^ uiFont = gcnew Drawing::Font("Segoe UI", 14, FontStyle::Regular);
            e->Graphics->DrawString("Рахунок: " + game->score, uiFont, Brushes::Black, 15, 15);
            e->Graphics->DrawString("Час: " + game->timeLeft, uiFont, Brushes::Black, 15, 45);

            if (game->timeLeft <= 0) {
                String^ over = "Гру завершено!";
                int boxWidth = 350, boxHeight = 80;
                int cx = this->ClientSize.Width / 2;
                int cy = this->ClientSize.Height / 2;

                RectangleF boxRect = RectangleF(
                    static_cast<float>(cx - boxWidth / 2),
                    static_cast<float>(cy - boxHeight / 2),
                    static_cast<float>(boxWidth),
                    static_cast<float>(boxHeight)
                );

                SolidBrush^ bgBrush = gcnew SolidBrush(Color::FromArgb(180, 30, 30, 30));
                e->Graphics->FillRectangle(bgBrush, boxRect);

                Drawing::Font^ font = gcnew Drawing::Font("Segoe UI", 24, FontStyle::Bold);
                StringFormat^ format = gcnew StringFormat();
                format->Alignment = StringAlignment::Center;
                format->LineAlignment = StringAlignment::Center;

                e->Graphics->DrawString(over, font, Brushes::White, boxRect, format);

                btnRestart->Location = System::Drawing::Point(
                    (this->ClientSize.Width - btnRestart->Width) / 2,
                    (cy + boxHeight / 2 + 20)
                );
            }
        }

        System::Void MyForm_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
        {
            if (game->timeLeft > 0) {
                game->OnClick(e->X, e->Y);
            }
        }

        System::Void OnTimerTick(System::Object^ sender, System::EventArgs^ e) {
            if (game->timeLeft > 0) {
                game->Tick();
                this->Invalidate();
            }
            else {
                timer->Stop();
                btnRestart->Visible = true;
                btnRestart->BringToFront();
                this->Invalidate();
            }
        }

        System::Void OnRestartClick(System::Object^ sender, System::EventArgs^ e) {
            game->Restart(this->ClientSize.Width, this->ClientSize.Height);
            btnRestart->Visible = false;
            timer->Start();
        }
    };
}

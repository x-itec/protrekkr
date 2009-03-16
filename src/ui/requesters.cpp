// ------------------------------------------------------
// Protrekkr
// Based on Juan Antonio Arguelles Rius's NoiseTrekker.
//
// Copyright (C) 2008-2009 Franck Charlet.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//  1. Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//  2. Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL FRANCK CHARLET OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.
// ------------------------------------------------------

// ------------------------------------------------------
// Includes
#include "../include/ptk.h"

// ------------------------------------------------------
// Variables
int In_Requester = FALSE;
int Requester_Action = GUI_CMD_NOP;
static int Size_X;
static int Size_Y;
static int Pos_X;
static int Pos_Y;
static int Nbr_Lines;
static int Nbr_Buttons;
static char *Req_Txt_Lines[64];
static int Req_Txt_Pos_X[64];
static int Buttons_Size[64];
static int Buttons_Pos[64];
static int Buttons_Keys[64];
static char *Buttons_Text[64];
LPREQUESTER Current_Requester;
static int Pressed_Button;
static int Default_Button;
static int Cancel_Button;

// ------------------------------------------------------
// Functions
void Kill_Requester(void);

// ------------------------------------------------------
// Start a requester
int Display_Requester(LPREQUESTER Requester, int Action)
{
    int i;
    // Inhibit main actions
    In_Requester = TRUE;

    Current_Requester = Requester;

    // Minim mum size
    Size_X = 0;
    Size_Y = 0;

    // Register the action to return
    Requester_Action = Action;

    // Parse the text
    int Max_Buttons_Size;
    int Biggest_Button;
    char *txt = Requester->Text;
    char *txt_beg;
    i = 0;
    Nbr_Lines = 0;
    Nbr_Buttons = 0;
    Max_Buttons_Size = 0;
    
    Default_Button = -1;
    Cancel_Button = -1;

    Pressed_Button = 0;

    memset(Req_Txt_Lines, 0, sizeof(Req_Txt_Lines));

    txt_beg = txt;
    while(txt[0])
    {
        if(txt[0] == '\n')
        {
            Req_Txt_Lines[Nbr_Lines] = (char *) malloc(i + 1);
            memset(Req_Txt_Lines[Nbr_Lines], 0, i + 1);
            strncpy(Req_Txt_Lines[Nbr_Lines], txt_beg, i);
            Req_Txt_Pos_X[Nbr_Lines] = Get_Size_Text(Req_Txt_Lines[Nbr_Lines]);
            if(Req_Txt_Pos_X[Nbr_Lines] > Size_X)
            {
                Size_X = Req_Txt_Pos_X[Nbr_Lines];
                Get_Size_Text(Req_Txt_Lines[Nbr_Lines]);
            }
            Nbr_Lines++;
            i = 0;
            txt++;
            txt_beg = txt;
        }
        i++;
        txt++;
    }
    if(i > 0)
    {
        Req_Txt_Lines[Nbr_Lines] = (char *) malloc(i + 1);
        memset(Req_Txt_Lines[Nbr_Lines], 0, i + 1);
        strncpy(Req_Txt_Lines[Nbr_Lines], txt_beg, i);
        Req_Txt_Pos_X[Nbr_Lines] = Get_Size_Text(Req_Txt_Lines[Nbr_Lines]);
        if(Req_Txt_Pos_X[Nbr_Lines] > Size_X)
        {
            Size_X = Req_Txt_Pos_X[Nbr_Lines];
        }
        Nbr_Lines++;
    }

    // Parse the buttons
    LPREQUESTER_BUTTON Button;
    Button = Requester->Buttons;
    Biggest_Button = 0;
    while(Button)
    {
        Buttons_Text[Nbr_Buttons] = Button->Text;
        Buttons_Keys[Nbr_Buttons] = Button->Key;
        if(Get_Size_Text(Button->Text) + 42 > Biggest_Button)
        {
            Biggest_Button = Get_Size_Text(Button->Text) + 30;
        }
        // Record the buttons type
        switch(Button->Type)
        {
            case BUTTON_DEFAULT:
                Default_Button = Nbr_Buttons + 1;
                break;

            case BUTTON_CANCEL:
                Cancel_Button = Nbr_Buttons + 1;
                break;
        }
        Nbr_Buttons++;
        Button = (LPREQUESTER_BUTTON) Button->Next;
    }

    for(i = 0; i < Nbr_Buttons; i++)
    {
        Buttons_Size[i] = Biggest_Button;
        Max_Buttons_Size += Buttons_Size[i];
    }

    if(Max_Buttons_Size > Size_X) Size_X = Max_Buttons_Size;

    Size_X += 150;

    float Si = (float) Size_X / (float) Nbr_Buttons;
    float Pos_Si = 0.0f;

    for(i = 0; i < Nbr_Buttons; i++)
    {
        Buttons_Pos[i] = (int) (((Si - (float) Buttons_Size[i]) / 2.0f) + Pos_Si);
        Pos_Si += Si;
    }

    for(i = 0; i < Nbr_Lines; i++)
    {
        Req_Txt_Pos_X[i] = (Size_X - Req_Txt_Pos_X[i]) / 2;
    }

    Size_Y = (((Nbr_Lines + 5) * Font_Height) + 18);

    Pos_X = (CONSOLE_WIDTH - Size_X) / 2;
    Pos_Y = (CONSOLE_HEIGHT - Size_Y) / 2;
    return(0);
}

// ------------------------------------------------------
// Start a requester
int Check_Requester(LPREQUESTER Requester)
{
    int Pressed = 0;
    if(Current_Requester == Requester)
    {
        int i;
        Gui_Draw_Button_Box(Pos_X, Pos_Y, Size_X, Size_Y, "", BUTTON_NORMAL | BUTTON_DISABLED);
        Gui_Draw_Button_Box(Pos_X + 3, Pos_Y + 3, Size_X - 6, Size_Y - 6, "", BUTTON_PUSHED | BUTTON_DISABLED);
        Gui_Draw_Button_Box(Pos_X + 4, Pos_Y + 4, Size_X - 8, Size_Y - 8, "", BUTTON_NORMAL | BUTTON_DISABLED);

        for(i = 0; i < Nbr_Lines; i++)
        {
            PrintXY(Pos_X + Req_Txt_Pos_X[i],
                    Pos_Y + ((i + 1) * Font_Height) + (Font_Height / 2),
                    USE_FONT, Req_Txt_Lines[i]);
        }

        for(i = 0; i < Nbr_Buttons; i++)
        {
            Gui_Draw_Button_Box(Pos_X + Buttons_Pos[i] - 1, Pos_Y + (Size_Y - Font_Height) - 16 - 1,
                                Buttons_Size[i] + 2, 16 + 2, "", BUTTON_PUSHED | BUTTON_DISABLED);
            if(Default_Button == i + 1)
            {
                // Add a box around the default button
                Gui_Draw_Button_Box(Pos_X + Buttons_Pos[i] - 2, Pos_Y + (Size_Y - Font_Height) - 16 - 2,
                                    Buttons_Size[i] + 4, 16 + 4, "", BUTTON_PUSHED | BUTTON_DISABLED);
            }
            Gui_Draw_Button_Box(Pos_X + Buttons_Pos[i],
                                Pos_Y + (Size_Y - Font_Height) - 16,
                                Buttons_Size[i], 16,
                                Buttons_Text[i],
                                BUTTON_NORMAL | BUTTON_TEXT_CENTERED);
        }
        if(Pressed_Button)
        {
            Kill_Requester();
            Pressed = Pressed_Button;
            Pressed_Button = 0;
            gui_action = Requester_Action;
            Requester_Action = GUI_CMD_NOP;
        }
    }
    // Return the clicked button
    return(Pressed);
}

// ------------------------------------------------------
// Mouse Handler
void Mouse_Handler_Requester(void)
{
    int i;

    if(Mouse.button_oneshot & MOUSE_LEFT_BUTTON)
    {
        for(i = 0; i < Nbr_Buttons; i++)
        {
            if(zcheckMouse(Pos_X + Buttons_Pos[i],
                           Pos_Y + (Size_Y - Font_Height) - 16, Buttons_Size[i], 16))
            {
                Pressed_Button = i + 1;
            }
        }
    }
}

// ------------------------------------------------------
// KeyBoard ShortCut Handler
void Keyboard_Handler_Requester(void)
{
    int i;

    for(i = 0; i < Nbr_Buttons; i++)
    {
        if(Keys[Buttons_Keys[i]])
        {
            Pressed_Button = i + 1;
        }
    }

    if(Keys[SDLK_ESCAPE])
    {
        if(Cancel_Button != -1)
        {
            Pressed_Button = Cancel_Button;
        }
    }

    if(Keys[SDLK_RETURN] || Keys[SDLK_KP_ENTER])
    {
        if(Default_Button != -1)
        {
            Pressed_Button = Default_Button;
        }
    }
}

// ------------------------------------------------------
// Free requester resources
void Kill_Requester(void)
{
    int i;

    for(i = 0; i < Nbr_Lines; i++)
    {
        if(Req_Txt_Lines[Nbr_Lines]) free(Req_Txt_Lines[Nbr_Lines]);
        Req_Txt_Lines[Nbr_Lines] = NULL;
    }
    Current_Requester = NULL;
    Actupated(0);
}
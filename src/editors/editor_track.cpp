// ------------------------------------------------------
// Protrekkr
// Written by Franck Charlet
// Based on the work of Juan Antonio Arguelles Rius 
// ------------------------------------------------------

// ------------------------------------------------------
// Includes
#include "include/editor_track.h"

// ------------------------------------------------------
// Functions
void Draw_Track_Ed(void)
{
    Draw_Editors_Bar(USER_SCREEN_TRACK_EDIT);

    Gui_Draw_Button_Box(0, 447, fsize, 130, "", BUTTON_NORMAL | BUTTON_DISABLED);
    Gui_Draw_Flat_Box("Track: Properties & Fx Send");

    Gui_Draw_Button_Box(508, 468, 60, 16, "Track", BUTTON_NORMAL | BUTTON_DISABLED);
    Gui_Draw_Button_Box(570, 468, 60, 16, "Delay Send", BUTTON_NORMAL | BUTTON_DISABLED);
    Gui_Draw_Button_Box(508, 530, 60, 16, "Solo Track", BUTTON_NORMAL);
    Gui_Draw_Button_Box(508, 548, 60, 16, "Un-mute All", BUTTON_NORMAL);

    Gui_Draw_Button_Box(8, 468, 224, 96, "Analog Filter Emulation", BUTTON_NORMAL | BUTTON_DISABLED);
    Gui_Draw_Button_Box(18, 484, 56, 16, "CutOff Frq.", BUTTON_NORMAL | BUTTON_DISABLED);
    Gui_Draw_Button_Box(18, 502, 56, 16, "Reso.", BUTTON_NORMAL | BUTTON_DISABLED);
    Gui_Draw_Button_Box(18, 520, 56, 16, "Type", BUTTON_NORMAL | BUTTON_DISABLED);
    Gui_Draw_Button_Box(18, 538, 56, 16, "Inertia", BUTTON_NORMAL | BUTTON_DISABLED);

    Gui_Draw_Button_Box(240, 468, 260, 96, "Distorsion/Reverb/Pan", BUTTON_NORMAL | BUTTON_DISABLED);
    Gui_Draw_Button_Box(248, 484, 56, 16, "Threshold", BUTTON_NORMAL | BUTTON_DISABLED);
    Gui_Draw_Button_Box(248, 502, 56, 16, "Clamp", BUTTON_NORMAL | BUTTON_DISABLED);
    Gui_Draw_Button_Box(248, 520, 56, 16, "Reverb", BUTTON_NORMAL | BUTTON_DISABLED);
    Gui_Draw_Button_Box(248, 538, 56, 16, "Pan", BUTTON_NORMAL | BUTTON_DISABLED);
    Gui_Draw_Button_Box(456, 484, 40, 16, "Flat2C", BUTTON_NORMAL);
    Gui_Draw_Button_Box(456, 502, 40, 16, "Flat2T", BUTTON_NORMAL);
    Gui_Draw_Button_Box(456, 538, 40, 16, "Center", BUTTON_NORMAL);
    Gui_Draw_Button_Box(570, 512, 60, 16, "Midi Chnl.", BUTTON_NORMAL | BUTTON_DISABLED);
}
   
void Actualize_Track_Ed(char gode)
{
    if(userscreen == USER_SCREEN_TRACK_EDIT)
    {

        if(gode == 0)
        {
            if(ped_track > MAX_TRACKS - 1) ped_track = 0;
            if(ped_track < 0) ped_track = MAX_TRACKS - 1;
            value_box(508, 486, ped_track, BUTTON_NORMAL | BUTTON_TEXT_CENTERED);
        }

        if(gode == 0 || gode == 1)
        {
            if(TCut[ped_track] < 0) TCut[ped_track] = 0;
            if(TCut[ped_track] > 127) TCut[ped_track] = 127;
            Realslider(77, 484, (int) TCut[ped_track], TRUE);
        }

        if(gode == 0 || gode == 2)
        {
            if(FRez[ped_track] < 0) FRez[ped_track] = 0;
            if(FRez[ped_track] > 127) FRez[ped_track] = 127;
            Realslider(77, 502, FRez[ped_track], TRUE);
        }

        if(gode == 0 || gode == 3)
        {
            if(ICut[ped_track] > 0.0078125f) ICut[ped_track] = 0.0078125f;
            if(ICut[ped_track] < 0.00006103515625f) ICut[ped_track] = 0.00006103515625f;
            Realslider(77, 538, f2i(ICut[ped_track] * 16384.0f), TRUE);
        }

        if(gode == 0 || gode == 4)
        {
            if(FType[ped_track] < 0) FType[ped_track] = 0;
            if(FType[ped_track] >= MAX_FILTER) FType[ped_track] = MAX_FILTER;
            switch(FType[ped_track])
            {
                case 0: Gui_Draw_Button_Box(139, 520, 84, 16, "LoPass -12db", BUTTON_NORMAL); break;
                case 1: Gui_Draw_Button_Box(139, 520, 84, 16, "HiPass", BUTTON_NORMAL); break;
                case 2: Gui_Draw_Button_Box(139, 520, 84, 16, "BandPass", BUTTON_NORMAL); break;
                case 3: Gui_Draw_Button_Box(139, 520, 84, 16, "BandReject", BUTTON_NORMAL); break;
                case 4: Gui_Draw_Button_Box(139, 520, 84, 16, "Filter Off", BUTTON_NORMAL); break;
                case 5: Gui_Draw_Button_Box(139, 520, 84, 16, "LoPass -24db", BUTTON_NORMAL); break;
                case 6: Gui_Draw_Button_Box(139, 520, 84, 16, "LoPass -48db", BUTTON_NORMAL); break;
                case 7: Gui_Draw_Button_Box(139, 520, 84, 16, "LP-24 [Stereo]", BUTTON_NORMAL); break;
                case 8: Gui_Draw_Button_Box(139, 520, 84, 16, "A. Mod. [Mono]", BUTTON_NORMAL); break;
                case 9: Gui_Draw_Button_Box(139, 520, 84, 16, "A. Mod. [Stereo]", BUTTON_NORMAL); break;
                case 10: Gui_Draw_Button_Box(139, 520, 84, 16, "Single [Mono]", BUTTON_NORMAL); break;
                case 11: Gui_Draw_Button_Box(139, 520, 84, 16, "Single [Stereo]", BUTTON_NORMAL); break;
                case 12: Gui_Draw_Button_Box(139, 520, 84, 16, "ParaEq -15db", BUTTON_NORMAL); break;
                case 13: Gui_Draw_Button_Box(139, 520, 84, 16, "ParaEq -6db", BUTTON_NORMAL); break;
                case 14: Gui_Draw_Button_Box(139, 520, 84, 16, "ParaEq +6db", BUTTON_NORMAL); break;
                case 15: Gui_Draw_Button_Box(139, 520, 84, 16, "ParaEq +15db", BUTTON_NORMAL); break;
                case 16: Gui_Draw_Button_Box(139, 520, 84, 16, "Custom Delta", BUTTON_NORMAL); break;
                case 17: Gui_Draw_Button_Box(139, 520, 84, 16, "Comp. Distort L", BUTTON_NORMAL); break;
                case 18: Gui_Draw_Button_Box(139, 520, 84, 16, "Comp. Distort M", BUTTON_NORMAL); break;
                case 19: Gui_Draw_Button_Box(139, 520, 84, 16, "Comp. Distort H", BUTTON_NORMAL); break;
                case 20: Gui_Draw_Button_Box(139, 520, 84, 16, "Comp. Distort", BUTTON_NORMAL); break;
                case 21: Gui_Draw_Button_Box(139, 520, 84, 16, "W-HP12 [Mono]", BUTTON_NORMAL); break;
                case 22: Gui_Draw_Button_Box(139, 520, 84, 16, "W-HP12 [Stereo]", BUTTON_NORMAL); break;
                case 23: Gui_Draw_Button_Box(139, 520, 84, 16, "W-HP24 [Mono]", BUTTON_NORMAL); break;
            }
            value_box(77, 520, FType[ped_track], BUTTON_NORMAL | BUTTON_TEXT_CENTERED);
        }

        if(gode == 0 || gode == 5)
        {
            if(DSend[ped_track] < 0) DSend[ped_track] = 0;
            if(DSend[ped_track] > 1.0f) DSend[ped_track] = 1.0f;
            Realslider(308, 520, int(DSend[ped_track] * 128.0f), TRUE);
        }

        if(gode == 0 || gode == 6)
        {
            if(CSend[ped_track] < 0) CSend[ped_track] = 0;
            if(CSend[ped_track] > 127) CSend[ped_track] = 127;
            value_box(570, 486, CSend[ped_track], BUTTON_NORMAL | BUTTON_TEXT_CENTERED);
            CCoef[ped_track] = float((float) CSend[ped_track] / 127.0f);
        }

        if(gode == 0 || gode == 7)
        {
            if(DThreshold[ped_track] < 0) DThreshold[ped_track] = 0;
            if(DThreshold[ped_track] > 65535) DThreshold[ped_track] = 65535;
            Realslider(308, 484, (int) DThreshold[ped_track] / 512, TRUE);
        }

        if(gode == 0 || gode == 8)
        {
            if(DClamp[ped_track] < 0) DClamp[ped_track] = 0;
            if(DClamp[ped_track] > 65535) DClamp[ped_track] = 65535;
            Realslider(308, 502, (int) DClamp[ped_track] / 512, TRUE);
        }

        if(gode == 0 || gode == 9)
        {
            if(TPan[ped_track] < 0.0f) TPan[ped_track] = 0.0f;
            if(TPan[ped_track] > 1.0f) TPan[ped_track] = 1.0f;
            ComputeStereo(ped_track);
            Realslider(308, 538, f2i(TPan[ped_track] * 127.0f), TRUE);
        }

        if(gode == 0 || gode == 10)
        {
            if(TRACKSTATE[ped_track]) Gui_Draw_Button_Box(508, 512, 60, 16, "Un-Mute", BUTTON_PUSHED);
            else Gui_Draw_Button_Box(508, 512, 60, 16, "Mute Track", BUTTON_NORMAL);
        }

        if(gode == 0 || gode == 11)
        {
            if(TRACKMIDICHANNEL[ped_track] > 15) TRACKMIDICHANNEL[ped_track] = 0;
            if(TRACKMIDICHANNEL[ped_track] < 0) TRACKMIDICHANNEL[ped_track] = 15;
            Gui_Draw_Arrows_Number_Box2(570, 530, TRACKMIDICHANNEL[ped_track] + 1, BUTTON_NORMAL | BUTTON_TEXT_CENTERED);
        }

        if(gode == 0 || gode == 12)
        {
            if(Disclap[ped_track]) Gui_Draw_Button_Box(570, 548, 60, 16, "Distort On", BUTTON_PUSHED);
            else Gui_Draw_Button_Box(570, 548, 60, 16, "Distort Off", BUTTON_NORMAL);
        }

        if(trkchan == true)
        {
            Actupated(0);
            trkchan = false;
        }
    } // Userscreen match found
}

void Mouse_Left_Track_Ed(void)
{
    if(userscreen == USER_SCREEN_TRACK_EDIT)
    {
        if(zcheckMouse(77, 520, 16, 16) && FType[ped_track] > 0)
        {
            ResetFilters(ped_track);
            FType[ped_track]--;
            teac = 4;
            gui_action = GUI_CMD_UPDATE_TRACK_ED;
        }
        if(zcheckMouse(121, 520, 16, 16) && FType[ped_track] < MAX_FILTER)
        {
            ResetFilters(ped_track);
            FType[ped_track]++;
            teac = 4;
            gui_action = GUI_CMD_UPDATE_TRACK_ED;
        }
        if(zcheckMouse(508, 486, 16, 16))
        {
            ped_track--;
            teac = 0;
            gui_action = GUI_CMD_UPDATE_TRACK_ED;
            trkchan = true;
        }
        if(zcheckMouse(552, 486, 16, 16))
        {
            ped_track++;
            teac = 0;
            gui_action = GUI_CMD_UPDATE_TRACK_ED;
            trkchan = true;
        }  
        if(zcheckMouse(570, 486, 16, 16))
        {
            CSend[ped_track]--;
            teac = 6;
            gui_action = GUI_CMD_UPDATE_TRACK_ED;
        }
        if(zcheckMouse(614, 486, 16, 16))
        {
            CSend[ped_track]++;
            teac = 6;
            gui_action = GUI_CMD_UPDATE_TRACK_ED;
        }  

        if(zcheckMouse(456, 484, 40, 16))
        {
            DThreshold[ped_track] = DClamp[ped_track];
            teac = 7;
            gui_action = GUI_CMD_UPDATE_TRACK_ED;
        }  
        if(zcheckMouse(456, 502, 40, 16))
        {
            DClamp[ped_track] = DThreshold[ped_track];
            teac = 8;
            gui_action = GUI_CMD_UPDATE_TRACK_ED;
        }  
        if(zcheckMouse(456, 538, 40, 16))
        {
            TPan[ped_track] = 0.5f;
            gui_action = GUI_CMD_UPDATE_TRACK_ED;
            teac = 9;
        }  

        if(zcheckMouse(570, 530, 16, 16))
        {
            TRACKMIDICHANNEL[ped_track]--;
            gui_action = GUI_CMD_UPDATE_TRACK_ED;
            teac = 11;
        }  
        if(zcheckMouse(614, 530, 16, 16))
        {
            TRACKMIDICHANNEL[ped_track]++;
            gui_action = GUI_CMD_UPDATE_TRACK_ED;
            teac = 11;
        }  

        // Mute track
        if(zcheckMouse(570, 548, 60, 16))
        {
            Disclap[ped_track] = !Disclap[ped_track];
            gui_action = GUI_CMD_UPDATE_TRACK_ED;
            teac = 12;
        }

        if(zcheckMouse(508, 512, 64, 16))
        {
            if(TRACKSTATE[ped_track] == 0) TRACKSTATE[ped_track] = 1;
            else TRACKSTATE[ped_track] = 0;
            gui_action = GUI_CMD_UPDATE_TRACK_ED;
            teac = 10;
            trkchan = true;
        }  

        // Solo track
        if(zcheckMouse(508, 530, 64, 16))
        {
            for(int solify = 0; solify < MAX_TRACKS; solify++)
            {
                TRACKSTATE[solify] = 1;
            }
            TRACKSTATE[ped_track] = 0;
            gui_action = GUI_CMD_UPDATE_TRACK_ED;
            trkchan = true;
            teac = 10;
        }  

        // Unmute all tracks
        if(zcheckMouse(508, 548, 88, 16))
        {
            for(int solify = 0; solify < MAX_TRACKS; solify++)
            {
                TRACKSTATE[solify] = 0;
            }
            gui_action = GUI_CMD_UPDATE_TRACK_ED;
            trkchan = true;
            teac = 10;
        }  
    } // Userscreen 1
}

void Mouse_Right_Track_Ed(void)
{
    if(userscreen == USER_SCREEN_TRACK_EDIT)
    {
        if(zcheckMouse(570, 486, 16, 16) == 1)
        {
            CSend[ped_track] -= 16;
            gui_action = GUI_CMD_UPDATE_TRACK_ED;
        }
        if(zcheckMouse(614, 486, 16, 16) == 1)
        {
            CSend[ped_track] += 16;
            gui_action = GUI_CMD_UPDATE_TRACK_ED;
        }  

        if(zcheckMouse(77, 520, 16, 16) && FType[ped_track] > 0)
        {
            ResetFilters(ped_track);
            FType[ped_track] -= 16;
            teac = 4;
            gui_action = GUI_CMD_UPDATE_TRACK_ED;
        }
        if(zcheckMouse(121, 520, 16, 16) && FType[ped_track] < MAX_FILTER)
        {
            ResetFilters(ped_track);
            FType[ped_track] += 16;
            teac = 4;
            gui_action = GUI_CMD_UPDATE_TRACK_ED;
        }
    }
}

void Mouse_Sliders_Track_Ed(void)
{
    if(userscreen == USER_SCREEN_TRACK_EDIT)
    {
        if(zcheckMouse(77, 484, 148, 16)) gui_action = GUI_CMD_SET_TRACK_CUTOFF_FREQ;
        if(zcheckMouse(77, 502, 148, 16)) gui_action = GUI_CMD_SET_TRACK_RESONANCE;
        if(zcheckMouse(77, 538, 148, 16)) gui_action = GUI_CMD_SET_TRACK_INERTIA;
        if(zcheckMouse(308, 484, 148, 16)) gui_action = GUI_CMD_SET_TRACK_THRESHOLD;
        if(zcheckMouse(308, 502, 148, 16)) gui_action = GUI_CMD_SET_TRACK_CLAMP;
        if(zcheckMouse(308, 520, 148, 16)) gui_action = GUI_CMD_SET_TRACK_REVERB_SEND;
        if(zcheckMouse(308, 538, 148, 16)) gui_action = GUI_CMD_SET_TRACK_PANNING;
    }
}
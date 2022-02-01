// SPDX-License-Identifier: GPL-2.0-only
// PROJECT NAME:  MP3Edit
// COPYRIGHT:     Copyright © 2022 Sean Cassell <sean.cassell@outlook.com>
// FILENAME:      GetControlsVector.cpp
// FILE PURPOSE:  [To be added]
//                


/* **************************** INCLUDED HEADERS **************************** */
#include "GetControlsVector.hpp"
#include "../ControlVars.h"


/* ************************** FUNCTION DEFINITIONS ************************** */
auto Utils::GetControlsVector() noexcept->std::vector<SControl> {
	constexpr static const size_t kCONTROL_VEC_SIZE = 21ui64;
	std::vector<SControl> vecControls(kCONTROL_VEC_SIZE);
	
	// Define the dimensions (top, left, width, height) for each control:
	// [1] Labels (STATIC):
	SDimensions dimLblInstructions{
		CONTROL_SEPARATOR, CONTROL_SEPARATOR, LABEL_WIDTH, LABEL_HEIGHT
	};
	SDimensions dimLblTitle{
		(dimLblInstructions.Top + dimLblInstructions.Height + CONTROL_SEPARATOR), 
		CONTROL_SEPARATOR, LABEL_WIDTH, LABEL_HEIGHT
	};
	SDimensions dimLblArtist{
		(dimLblTitle.Top + dimLblTitle.Height + CONTROL_SEPARATOR), 
		CONTROL_SEPARATOR, LABEL_WIDTH, LABEL_HEIGHT
	};
	SDimensions dimLblAlbum{
		(dimLblArtist.Top + dimLblArtist.Height + CONTROL_SEPARATOR), 
		CONTROL_SEPARATOR, LABEL_WIDTH, LABEL_HEIGHT
	};
	SDimensions dimLblYear{
		(dimLblAlbum.Top + dimLblAlbum.Height + CONTROL_SEPARATOR), 
		CONTROL_SEPARATOR, LABEL_WIDTH, LABEL_HEIGHT
	};
	SDimensions dimLblTrack{
		(dimLblYear.Top + dimLblYear.Height + CONTROL_SEPARATOR), 
		CONTROL_SEPARATOR, LABEL_WIDTH, LABEL_HEIGHT
	};
	SDimensions dimLblComment{
		(dimLblTrack.Top + dimLblTrack.Height + CONTROL_SEPARATOR), 
		CONTROL_SEPARATOR, LABEL_WIDTH, LABEL_HEIGHT
	};
	SDimensions dimLblAlbumArtist{
		(dimLblComment.Top + dimLblComment.Height + CONTROL_SEPARATOR), 
		CONTROL_SEPARATOR, LABEL_WIDTH, LABEL_HEIGHT
	};
	SDimensions dimLblGenre{
		(dimLblAlbumArtist.Top + dimLblAlbumArtist.Height + CONTROL_SEPARATOR), 
		CONTROL_SEPARATOR, LABEL_WIDTH, LABEL_HEIGHT
	};
	SDimensions dimLblComposer{
		(dimLblGenre.Top + dimLblGenre.Height + CONTROL_SEPARATOR), 
		CONTROL_SEPARATOR, LABEL_WIDTH, LABEL_HEIGHT
	};
	SDimensions dimLblDiscNumber{
		(dimLblComposer.Top + dimLblC.Height + CONTROL_SEPARATOR), 
		CONTROL_SEPARATOR, LABEL_WIDTH, LABEL_HEIGHT
	};
	
	// [2] Textboxes (EDIT):
	int32_t TextboxXCoord = (dimLblTitle.Left + LABEL_WIDTH + CONTROL_SEPARATOR);
	SDimensions dimTxtTitle{
		CONTROL_SEPARATOR, 
		TextboxXCoord, 
		TEXTBOX_WIDTH, TEXTBOX_HEIGHT
	};
	SDimensions dimTxtArtist{
		(dimTxtTitle.Top + dimTxtTitle.Height + CONTROL_SEPARATOR), 
		TextboxXCoord, 
		TEXTBOX_WIDTH, TEXTBOX_HEIGHT
	};
	SDimensions dimTxtAlbum{
		(dimTxtArtist.Top + dimTxtArtist.Height + CONTROL_SEPARATOR), 
		TextboxXCoord, 
		TEXTBOX_WIDTH, TEXTBOX_HEIGHT
	};
	SDimensions dimTxtYear{
		(dimTxtAlbum.Top + dimTxtAlbum.Height + CONTROL_SEPARATOR), 
		TextboxXCoord, 
		TEXTBOX_WIDTH, TEXTBOX_HEIGHT
	};
	SDimensions dimTxtTrack{
		(dimTxtYear.Top + dimTxtYear.Height + CONTROL_SEPARATOR), 
		TextboxXCoord, 
		TEXTBOX_WIDTH, TEXTBOX_HEIGHT
	};
	SDimensions dimTxtComment{
		(dimTxtTrack.Top + dimTxtTrack.Height + CONTROL_SEPARATOR), 
		TextboxXCoord, 
		TEXTBOX_WIDTH, TEXTBOX_HEIGHT
	};
	SDimensions dimTxtAlbumArtist{
		(dimTxtComment.Top + dimTxtComment.Height + CONTROL_SEPARATOR), 
		TextboxXCoord, 
		TEXTBOX_WIDTH, TEXTBOX_HEIGHT
	};
	// Note: When determining the Y-coordinate ('top') of 'txtComposer', be 
	//       sure to factor in that 'ddlGenre' is between 'txtAlbumArtist' and 
	//       'txtComposer'.
	SDimensions dimTxtComposer{
		(dimTxtAlbumArtist.Top + dimTxtAlbumArtist.Height + CONTROL_SEPARATOR
		 + DROPDOWN_HEIGHT + CONTROL_SEPARATOR), 
		TextboxXCoord, 
		TEXTBOX_WIDTH, TEXTBOX_HEIGHT
	};
	SDimensions dimTxtDiscNumber{
		(dimTxtComposer.Top + dimTxtComposer.Height + CONTROL_SEPARATOR), 
		TextboxXCoord, 
		TEXTBOX_WIDTH, TEXTBOX_HEIGHT
	};
	
	// [3] ComboBoxes (COMBOBOX):
	SDimensions dimDllGenre{
		(dimTxtAlbumArtist.Top + dimTxtAlbumArtist.Height + CONTROL_SEPARATOR), 
		TextboxXCoord, 
		TEXTBOX_WIDTH, TEXTBOX_HEIGHT
	};
	
	// Create an instance of the 'SControl' class for each control defined in 
	// the "../ControlVars.h" header:
	// [1] Labels (STATIC):
	SControl sconLblInstructions(ID_LBL_INSTRUCTIONS, 
								 hLblInstructions, 
								 lblInstructions, 
								 dimLblInstructions, 
								 Style::LabelStyle);
	SControl sconLblTitle(ID_LBL_TITLE, 
						  hLblTitle, 
						  lblTitle, 
						  dimLblTitle, 
						  Style::LabelStyle);
	SControl sconLblArtist(ID_LBL_ARTIST, 
						   hLblArtist, 
						   lblArtist, 
						   dimLblArtist, 
						   Style::LabelStyle);
	SControl sconLblAlbum(ID_LBL_ALBUM, 
						  hLblAlbum, 
						  lblAlbum, 
						  dimLblAlbum, 
						  Style::LabelStyle);
	SControl sconLblYear(ID_LBL_YEAR, 
						 hLblYear, 
						 lblYear, 
						 dimLblYear, 
						 Style::LabelStyle);
	SControl sconLblTrack(ID_LBL_TRACK, 
						  hLblTrack, 
						  lblTrack, 
						  dimLblTrack, 
						  Style::LabelStyle);
	SControl sconLblComment(ID_LBL_COMMENT, 
							hLblComment, 
							lblComment, 
							dimLblComment, 
							Style::LabelStyle);
	SControl sconLblAlbumArtist(ID_LBL_ALBUMARTIST, 
								hLblAlbumArtist, 
								lblAlbumArtist, 
								dimLblAlbumArtist, 
								Style::LabelStyle);
	SControl sconLblGenre(ID_LBL_GENRE, 
						  hLblGenre, 
						  lblGenre, 
						  dimLblGenre, 
						  Style::LabelStyle);
	SControl sconLblComposer(ID_LBL_COMPOSER, 
							 hLblComposer, 
							 lblComposer, 
							 dimLblComposer, 
							 Style::LabelStyle);
	SControl sconLblDiscNumber(ID_LBL_DISCNUMBER, 
							   hLblDiscNumber, 
							   lblDiscNumber, 
							   dimLblDiscNumber, 
							   Style::LabelStyle);
	sconLblInstructions.m_Type = SType::Label;
	sconLblTitle.m_Type        = SType::Label;
	sconLblArtist.m_Type       = SType::Label;
	sconLblAlbum.m_Type        = SType::Label;
	sconLblYear.m_Type         = SType::Label;
	sconLblTrack.m_Type        = SType::Label;
	sconLblComment.m_Type      = SType::Label;
	sconLblAlbumArtist.m_Type  = SType::Label;
	sconLblGenre.m_Type        = SType::Label;
	sconLblComposer.m_Type     = SType::Label;
	sconLblDiscNumber.m_Type   = SType::Label;
	
	// [2] Textboxes (EDIT):
	SControl sconTxtTitle(ID_TXT_TITLE, 
						  hTxtTitle, 
						  txtTitle, 
						  dimTxtTitle, 
						  Style::EditStyle);
	SControl sconTxtArtist(ID_TXT_ARTIST, 
						   hTxtArtist, 
						   txtArtist, 
						   dimTxtArtist, 
						   Style::EditStyle);
	SControl sconTxtAlbum(ID_TXT_ALBUM, 
						  hTxtAlbum, 
						  txtAlbum, 
						  dimTxtAlbum, 
						  Style::EditStyle);
	SControl sconTxtYear(ID_TXT_YEAR, 
						 hTxtYear, 
						 txtYear, 
						 dimTxtYear, 
						 Style::EditStyle);
	SControl sconTxtTrack(ID_TXT_TRACK, 
						  hTxtTrack, 
						  txtTrack, 
						  dimTxtTrack, 
						  Style::EditStyle);
	SControl sconTxtComment(ID_TXT_COMMENT, 
							hTxtComment, 
							txtComment, 
							dimTxtComment, 
							Style::EditStyle);
	SControl sconTxtAlbumArtist(ID_TXT_ALBUMARTIST, 
								hTxtAlbumArtist, 
								txtAlbumArtist, 
								dimTxtAlbumArtist, 
								Style::EditStyle);
	SControl sconTxtComposer(ID_TXT_COMPOSER, 
							 hTxtComposer, 
							 txtComposer, 
							 dimTxtComposer, 
							 Style::EditStyle);
	SControl sconTxtDiscNumber(ID_TXT_DISCNUMBER, 
							   hTxtDiscNumber, 
							   txtDiscNumber, 
							   dimTxtDiscNumber, 
							   Style::EditStyle);
	sconTxtTitle.m_Type        = SType::Edit;
	sconTxtArtist.m_Type       = SType::Edit;
	sconTxtAlbum.m_Type        = SType::Edit;
	sconTxtYear.m_Type         = SType::Edit;
	sconTxtTrack.m_Type        = SType::Edit;
	sconTxtComment.m_Type      = SType::Edit;
	sconTxtAlbumArtist.m_Type  = SType::Edit;
	sconTxtComposer.m_Type     = SType::Edit;
	sconTxtDiscNumber.m_Type   = SType::Edit;
	
	// [3] ComboBoxes (COMBOBOX):
	SControl sconDdlGenre(ID_DDL_GENRE, 
						  hDdlGenre, 
						  ddlGenre, 
						  dimDdlGenre, 
						  Style::ComboBoxStyle);
	sconDdlGenre.m_Type        = SType::ComboBox;
	
	// Add the instances of the 'SControl' class to 'vecControls':
	vecControls.emplace_back(sconLblInstructions);
	vecControls.emplace_back(sconLblTitle);
	vecControls.emplace_back(sconLblArtist);
	vecControls.emplace_back(sconLblAlbum);
	vecControls.emplace_back(sconLblYear);
	vecControls.emplace_back(sconLblTrack);
	vecControls.emplace_back(sconLblComment);
	vecControls.emplace_back(sconLblAlbumArtist);
	vecControls.emplace_back(sconLblGenre);
	vecControls.emplace_back(sconLblComposer);
	vecControls.emplace_back(sconLblDiscNumber);
	vecControls.emplace_back(sconTxtTitle);
	vecControls.emplace_back(sconTxtArtist);
	vecControls.emplace_back(sconTxtAlbum);
	vecControls.emplace_back(sconTxtYear);
	vecControls.emplace_back(sconTxtTrack);
	vecControls.emplace_back(sconTxtComment);
	vecControls.emplace_back(sconTxtAlbumArtist);
	vecControls.emplace_back(sconTxtComposer);
	vecControls.emplace_back(sconTxtDiscNumber);
	vecControls.emplace_back(sconDdlGenre);
	
	// Right-size 'vecControls':
	vecControls.shrink_to_fit();
	
	// Return 'vecControls' to the calling function:
	return vecControls;
}

#include "stdio.h"
#include "stdlib.h"
#include "GameScene.h"
#include "GameSceneMenu.h"
#include "pango/pango.h"


GameScene* GameSceneMenu_New()
{
	GameScene* ret = malloc(sizeof(GameScene));
	ret->GameTick = GameSceneMenu_GameTick;
	ret->Draw = GameSceneMenu_Draw;
	ret->KeyDown = GameSceneMenu_KeyDown;
	ret->Dispose = GameSceneMenu_Dispose;
	ret->Field = malloc(sizeof(GameSceneMenu_Field));

	GameSceneMenu_Field* field = ret->Field;

	/* set menu items */
	field->Menu = SList_New();
	GameSceneMenu_MenuItem* item1 = malloc(sizeof(GameSceneMenu_MenuItem));
	item1->Name = "ゲームスタート";
	item1->Behavior = GameSceneMenu_MenuItem_Start_Behavior;
	GameSceneMenu_MenuItem* item2 = malloc(sizeof(GameSceneMenu_MenuItem));
	item2->Name = "ゲームを終了する";
	item2->Behavior = GameSceneMenu_MenuItem_Exit_Behavior;
	
	field->Menu->Add(field->Menu,item1);
	field->Menu->Add(field->Menu,item2);

	field->SelectionIndex = 0;

	/* load images */
	/*
	field->logo_png = cairo_image_surface_create_from_png
	("logo.png");
	if(cairo_surface_status(field->logo_png) != CAIRO_STATUS_SUCCESS){
		perror("Couldn't load logo image");
		exit(EXIT_FAILURE);
	}
	*/

	/* set flag */
	field->StartFlag = false;

	printf("CREATED");
	fflush(stdout);
	return ret;
}

GameScene* GameSceneMenu_GameTick(void* this)
{
	GameScene* ptr = this;
	GameSceneMenu_Field* field = ptr->Field;
	
	if(field->StartFlag){
		return GameSceneMain_New();
	}
	return NULL;
}

void GameSceneMenu_Draw(void* this, cairo_t* cr,int width,int height)
{
	GameScene* ptr = this;
	GameSceneMenu_Field* field = ptr->Field;


	/* clear */
	cairo_set_source_rgba(cr,1.0,1.0,1.0,1.0);
	cairo_rectangle(cr,0,0,width,height);
	cairo_fill(cr);

	/* paint logo */
	/*
	cairo_save(cr);
	int logo_width = cairo_image_surface_get_width(field->logo_png)
	* 0.4 * ((double)width)/400;
	int logo_pos_x = width / 2 - logo_width / 2;
	cairo_translate(cr,logo_pos_x,0);
	cairo_scale(cr,0.4 * ((double)width)/400,0.4 * ((double)width)/400);
	cairo_set_source_surface(cr,field->logo_png,0,0);
	cairo_paint(cr);
	cairo_restore(cr);
	cairo_identity_matrix(cr);
	*/

	PangoLayout *layout;
	PangoFontDescription *desc;
	
	layout = pango_cairo_create_layout(cr);

	/* show title */
	pango_layout_set_text(layout, "お団子シューティング", -1);
	char fds[64];
	snprintf(fds,sizeof(fds),"IPAexGothic %dpx",40*width/400);
	desc = pango_font_description_from_string(fds);
	pango_layout_set_font_description(layout, desc);
	pango_layout_set_width(layout,pango_units_from_double(width));
	pango_layout_set_alignment(layout,PANGO_ALIGN_CENTER);
	pango_font_description_free(desc);
	cairo_set_source_rgb(cr, 1.0, 0.41, 0.70);
	pango_cairo_update_layout(cr, layout);
	pango_cairo_show_layout(cr, layout);
	
	/* draw menu items. */
	char fds_menuitem[64];
	int menuitem_px = 30 * width / 400;
	snprintf(fds_menuitem,sizeof(fds_menuitem),"IPAexGothic %dpx",
			menuitem_px);
	PangoFontDescription* pfd_menuitem =
		pango_font_description_from_string(fds_menuitem);
	pango_layout_set_font_description(layout,pfd_menuitem);
	pango_font_description_free(pfd_menuitem);
	int i;
	cairo_translate(cr,0,220 * width / 400);
	for(i = 0; i < field->Menu->Count(field->Menu); i++){
		
		GameSceneMenu_MenuItem* item =
		field->Menu->At(field->Menu,i)->Data;
		
		/* actually draw menuitem */
		cairo_translate(cr, 0, i * 30 * width / 400);
		pango_layout_set_text(layout,item->Name,-1);
		pango_layout_set_alignment(layout,PANGO_ALIGN_CENTER);
		pango_cairo_update_layout(cr,layout);
		pango_cairo_show_layout(cr,layout);

		/* draw focus arrow */
		if(i == field->SelectionIndex){
			cairo_save(cr);
			int w,h;
			pango_layout_get_size(layout,&w,&h);
			w = (int)(w/PANGO_SCALE);
			int pos_x = width / 2 - w / 2 - menuitem_px;
			cairo_translate(cr,pos_x,0);
			pango_layout_set_text(layout,">",-1);
			pango_layout_set_alignment(layout,PANGO_ALIGN_LEFT);
			pango_cairo_update_layout(cr,layout);
			pango_cairo_show_layout(cr,layout);
			cairo_restore(cr);
		}
	}


	g_object_unref(layout);

}

void GameSceneMenu_KeyDown(void* this,GameKeys key)
{
	GameScene* ptr = this;
	GameSceneMenu_Field* field = ptr->Field;
	if(key == GameKey_A)
	{
		GameSceneMenu_MenuItem* item = 
		field->Menu->At(field->Menu,field->SelectionIndex)->Data;

		item->Behavior(this);
	}
	if(key == GameKey_Up){
		field->SelectionIndex--;
		if(field->SelectionIndex < 0){
			field->SelectionIndex = 
			field->Menu->Count(field->Menu) - 1;
		}
	}
	if(key == GameKey_Down){
		field->SelectionIndex++;
		if(field->SelectionIndex >= field->Menu->Count(field->Menu)){
			field->SelectionIndex = 0;
		}
	}
}

/* Behaviors for each menuitem */
void GameSceneMenu_MenuItem_Start_Behavior(void* this)
{
	GameScene* ptr = this;
	GameSceneMenu_Field* field = ptr->Field;
	field->StartFlag = true;
}

void GameSceneMenu_MenuItem_Exit_Behavior(void* this)
{
	/* exit normally */ 
	exit(0);
}

void GameSceneMenu_Dispose(void* this)
{
	printf("DISPOSED");
	fflush(stdout);
	GameScene* ptr = this;
	free(ptr->Field);
	free(ptr);
}

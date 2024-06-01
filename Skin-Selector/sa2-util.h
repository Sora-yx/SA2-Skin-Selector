#pragma once


ObjectFunc(sub_470CC0, 0x470CC0);

#pragma pack(push, 8)
struct TailsCharObj2New
{
	CharObj2Base base;
	char field_1BC[40];
	NJS_POINT3 righthand_pos;
	NJS_POINT3 lefthand_pos;
	NJS_POINT3 rightfoot_pos;
	NJS_POINT3 leftfoot_pos;
	NJS_POINT3 head0_pos;
	NJS_POINT3 head1_pos;
	NJS_POINT3 head2_pos;
	NJS_POINT3 tailnode_pos;
	char field_2BC[36];
	NJS_POINT3 righthand_vec0;
	NJS_POINT3 lefthand_vec0;
	NJS_POINT3 righthand_vec1;
	NJS_POINT3 lefthand_vec1;
	NJS_POINT3 rightfoot_vec;
	NJS_POINT3 leftfoot_vec;
	NJS_POINT3 head0_vec;
	NJS_POINT3 head1_vec;
	NJS_POINT3 head2_vec;
	NJS_POINT3 tailnode_vec;
	char field_3BC[156];
	NJS_POINT3 tailOriginPos;
	char field_3BD[24];
	int tailIdk;
	JiggleInfo* tailJiggle0;
	JiggleInfo* tailJiggle1;
	NJS_TEXLIST* TextureList;
	ModelIndex* ModelList;
	AnimationIndex* MotionList;
	char field_4BC[36];
};
#pragma pack(pop)
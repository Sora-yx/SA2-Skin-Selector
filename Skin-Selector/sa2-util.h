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


FunctionPointer(void, DrawSubtitlesSA2, (Float a1, const char* hint, int timer, int language, DWORD* a5, int textType), 0x6B7580);

DataArray(NJS_OBJECT*, SonicEyesArray, 0x1A51AD0, 0x3);
DataArray(NJS_OBJECT*, AmyEyesArray, 0x1A519C4, 0x3);
DataArray(NJS_OBJECT*, ShadowEyesArray, 0x1A51888, 0x3);
DataArray(NJS_OBJECT*, MSEyesArray, 0x1A518F4, 0x3);
DataArray(NJS_OBJECT*, TikalEyesArray, 0x1A51CEC, 0x3);
DataArray(NJS_OBJECT*, KnuxEyesArray, 0x1A51BAC, 0x3);
DataArray(NJS_OBJECT*, RougeEyesArray, 0x1A51B6C, 0x3);
DataArray(NJS_OBJECT*, MilesEyesArray, 0x1A52150, 0x3);

DataPointer(ObjectMaster*, DrawSubtitlesPtr, 0x1AEFD50);


//void __usercall LoadEyesTrack(int pnum@<ebx>, NJS_OBJECT** a2@<edi>)
static const void* const LoadEyesTrackPtr = (void*)0x476530;
static inline void LoadEyesTrack(int pnum, NJS_OBJECT** a2)
{
	__asm
	{
		mov edi, [a2]
		mov ebx, [pnum]
		call LoadEyesTrackPtr
	}
}
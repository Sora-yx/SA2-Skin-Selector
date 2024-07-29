#pragma once

void LoadSonicJiggle(SonicCharObj2* sco2);
void LoadShadowJiggle(SonicCharObj2* sco2);
void LoadAmyJiggle(SonicCharObj2* sco2);
void LoadMilesJiggle(TailsCharObj2New* mco2);
void LoadKnuxJiggle(KnucklesCharObj2* kco2);
void LoadRougeJiggle(KnucklesCharObj2* kco2, bool isAlt);
void LoadTikalJiggle(KnucklesCharObj2* tco2);
void LoadSuperSonicJiggle(SuperSonicCharObj2* sco2);
void LoadSuperShadowJiggle(SuperSonicCharObj2* sco2);
void CheckAndLoadJiggle(const uint8_t pnum, const uint8_t charID2);
void InitJiggleHacks();
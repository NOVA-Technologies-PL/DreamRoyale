#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "csv_logic/character_buffs.csv" //Buff
#include "csv_logic/characters.csv" //postacie (wymagane dla Guardienne)
#include "csv_logic/area_effect_objects.csv" //NotInUse
#include "csv_logic/buildings.csv" //NotInUse
#include "csv_logic/actions.toml" //NotInUSe

#include "csv_logic/effects.csv"

typedef struct {
  char *name;
  void (*function)();
} Action;

void LittlePrinceChooseAttack(){
  if (attack_count == 0){
    LittlePrinceChangeAnim_to_0();
  } else if (attack_count == 2){
    LittlePrinceSpeedup1();
  } else if (attack_count == 4){
    LittlePrinceSpeedup2();
  } else if (attack_count == 5){
    LittlePrinceChangeAnim_to_2();
  }
}

void LittlePrinceSpeedup1(){
  SpawnBuff("LittlePrinceLvl1"); //Boost 100% (200) 1200 => 600
}

void LittlePrinceSpeedup2(){
  SpawnBuff("LittlePrinceLvlMax"); //Boost 200% (300) 1200 => 400
  PlayEffect("little_prince_maxed_speed");
}

void LittlePrinceChangeAnim_to_0(){
  SetAttackSequenceIndex(0);
}

void LittlePrinceChangeAnim_to_1(){
  SetAttackSequenceIndex(1);
  PlayEffect("little_prince_maxed_speed");
}

void LittlePrinceChangeAnim_to_2(){
  SetAttackSequenceIndex(2);
}

void SpawnChampionGuardCharge(){
  SpawnGuard("ChampionGuard"); //Guardienne
  SetTargetRadius(5000);
  SetAppearBehindAtDistance(2000); //Dystans na jakim Guardienne się pojawia
  SetPushBackStrength(3500);
  SetPushBackRadius(2500);
  SetDistanceProportinalPush(true);
  SetContinousPushBack(true);
  SetPushBackDamage(400); //Damage jaki zadaje Guardienne dashując na wrogie jednostki
  SetStopPrinceMovementUntilGuardArrive(true);
  SetForcePushback(true); //Wymusza Pushback na jednostkach które ignorują pushback
  SetPushbackInvisible(true);
  //SetFullPushbackCollisionCheck(true); //NotInUse
  SetActionDelay(825); //Delay: 0.825s
}

void LittlePrinceWaitGuard(){
  SetActionDuration(1500);
  SetActionCanBeCloned(false);
  SetGameTagsToSet("NO_MOVE");
  NextAction("Spawn_ChampionGuardCharge");
}

void Archer_EV1_Attack1(){
  SetAttackSequenceIndex(0);
}
void Archer_EV1_Attack2(){
  SetAttackSequenceIndex(1);
}
void Archer_EV1_AttackSelect(){
  if (!target_in_range(5000)){
    Archer_EV1_Attack2();
  } else {
    Archer_EV1_Attack1();
  }
}

void Recruit_EV1_StartCharge(){
  SpawnTime = 999999;
  SpawnBuff("RecruitsCharge_EV1");
  ParentGOAsSource = TRUE;
}

int main(){
  Action actions[] = {
    {"Spawn_ChampionGuardCharge", SpawnChampionGuardCharge},
    {"LittlePrinceWaitGuard", LittlePrinceWaitGuard},
    {"Archer_EV1_Attack1", Archer_EV1_Attack1},
    {"Archer_EV1_Attack2", Archer_EV1_Attack2},
    {"Archer_EV1_AttackSelect", Archer_EV1_AttackSelect},
    {"Recruit_EV1_StartCharge", Recruit_EV1_StartCharge}
  };
  int num_actions = sizeof(actions) / sizeof(actions[0]);

  for (int i=0; i < num_actions; i++) {
    printf("%s = %p\n", actions[i].name, actions[i].function);
  }

  return 0;
}


#ifndef AUTO_H
#define AUTO_H

typedef enum AutoOptions
{
  AUTO_NONE,
  AUTO_BLUE_SMALL,
  AUTO_BLUE_LARGE,
  AUTO_RED_SMALL,
  AUTO_RED_LARGE,
  AUTO_SKILLS
} AutoOptions;

extern AutoOptions chosenAuto;

/**
 * Action in the beginning to deploy
 */
void deploy();
void autoScoreSmall(AutoColor alliance, bool needsOuttake, bool needsReset);
void autoRunOfFour(AutoColor alliance, bool backUp, bool getFifth);
void autoRunOfThree(AutoColor alliance, bool backUpTo4, bool get2Stack);

void autoSkills();
void autoSmall9Pt(AutoColor alliance);
void autoSmall8Pt(AutoColor alliance);
void autoSmall7Pt(AutoColor alliance);
void autoSmall6Pt(AutoColor alliance);
void autoSmall5Pt(AutoColor alliance);



void autoSkillsSuperSafe();
void autoBlueSmallSafe();
void autoBlueSmallSuperSafe();
void autoBlueLargeSuperSafe();
void autoRedSmallSafe();
void autoRedSmallSuperSafe();
void autoRedLargeSuperSafe();

#endif

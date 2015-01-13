#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "GameObjectAI.h"
#include "Spell.h"
#include "Garrison.h"
#include "GarrisonScriptData.hpp"

/// Garrison cache generic script
class go_garrison_cache : public GameObjectScript
{
    public:
        /// Constructor
        go_garrison_cache() : 
            GameObjectScript("go_garrison_cache")
        { 
        
        }

        bool OnGossipHello(Player * p_Player, GameObject * p_GameObject)
        {
            if (p_Player->GetGarrison())
            {
                p_Player->GetGarrison()->RewardGarrisonCache();

                /// Alliance
                if (p_Player->HasQuest(MS::Garrison::Quests::QUEST_KEEPING_IT_TOGETHER) && p_GameObject)
                    p_Player->QuestObjectiveSatisfy(41327, 1, QUEST_OBJECTIVE_TYPE_CRITERIA, p_GameObject->GetGUID());

                /// Horde
                if (p_Player->HasQuest(MS::Garrison::Quests::QUEST_WHAT_WE_GOT) && p_GameObject)
                {
                    p_Player->QuestObjectiveSatisfy(41325, 2, QUEST_OBJECTIVE_TYPE_CRITERIA, p_GameObject->GetGUID());

                    Creature * l_Creature = p_Player->FindNearestCreature(MS::Garrison::NPCs::NPC_LADY_SENA, 15);

                    if (l_Creature)
                        l_Creature->AI()->Talk(0);
                }
            }

            return false;
        }

};

/// Garrison cache generic script
class go_garrison_outhouse : public GameObjectScript
{
    public:
        /// Constructor
        go_garrison_outhouse() :
            GameObjectScript("go_garrison_outhouse")
        { 
        
        }

        bool OnGossipHello(Player * p_Player, GameObject * p_GameObject)
        {
            p_Player->CastSpell(p_Player, MS::Garrison::Spells::SPELL_RELIEVED);

            if (!p_Player->GetAchievementMgr().HasAchieved(MS::Garrison::Achievements::ACHIEVEMENT_STAYING_REGULAR))
                p_Player->GetAchievementMgr().CompletedAchievement(sAchievementStore.LookupEntry(MS::Garrison::Achievements::ACHIEVEMENT_STAYING_REGULAR), nullptr);

            return false;
        }

};

void AddSC_Garrison_GO()
{
    new go_garrison_cache;
    new go_garrison_outhouse;
}
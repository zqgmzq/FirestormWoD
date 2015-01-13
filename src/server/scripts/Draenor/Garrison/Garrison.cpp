#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "GameObjectAI.h"
#include "Spell.h"
#include "Garrison.h"
#include "GarrisonScriptData.hpp"

class PlayerScript_Garrison: public PlayerScript
{
    public:
        PlayerScript_Garrison()
            : PlayerScript("PlayerScript_Garrison")
        {

        }

        /// Called when player rewards some quest
        virtual void OnQuestReward(Player* p_Player, const Quest* p_Quest) override
        {
            if (p_Player && p_Player->IsInGarrison() && p_Quest)
                p_Player->GetGarrison()->OnQuestReward(p_Quest);
        }

};

class spell_garrison_hearthstone: public SpellScriptLoader
{
    public:
        /// Constructor
        spell_garrison_hearthstone() 
            : SpellScriptLoader("spell_garrison_hearthstone")
        { 

        }

        /// Spell script
        class spell_garrison_hearthstone_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_garrison_hearthstone_SpellScript);

            /// Function called on server startup, if returns false script won't be used in core
            /// use for: dbc/template data presence/correctness checks
            bool Validate(SpellInfo const* p_SpellEntry) override
            {
                if (!sSpellMgr->GetSpellInfo(MS::Garrison::Spells::SPELL_GARRISON_HEARTHSTONE))
                    return false;

                return true;
            }

            /// On spell check cast
            SpellCastResult HandleCheckCast()
            {
                Player * l_Player = GetCaster()->ToPlayer();

                if (GetCaster()->isInCombat() && l_Player)
                {
                    l_Player->SendEquipError(EQUIP_ERR_NOT_IN_COMBAT, GetSpell()->m_CastItem, NULL);
                    return SPELL_FAILED_CUSTOM_ERROR;
                }

                if (l_Player && !l_Player->GetGarrison())
                    return SPELL_FAILED_GARRISON_NOT_OWNED;

                return SPELL_CAST_OK;
            }

            /// On spell EFFECT_0 dummy proc
            void HandleDummy(SpellEffIndex p_EffectIndex)
            {
                Player  * l_Player = GetCaster()->ToPlayer();

                if (l_Player && l_Player->GetGarrison() && l_Player->GetGarrison()->GetGarrisonSiteLevelEntry())
                {
                    Garrison * l_Garrison = l_Player->GetGarrison();

                    uint32 l_Index = (l_Garrison->GetGarrisonFactionIndex() * GARRISON_MAX_LEVEL) + (l_Garrison->GetGarrisonSiteLevelEntry()->Level - 1);

                    float l_X = MS::Garrison::gGarrisonHearthStoneTeleportCoord[l_Index][0];
                    float l_Y = MS::Garrison::gGarrisonHearthStoneTeleportCoord[l_Index][1];
                    float l_Z = MS::Garrison::gGarrisonHearthStoneTeleportCoord[l_Index][2];
                    float l_O = MS::Garrison::gGarrisonHearthStoneTeleportCoord[l_Index][3];

                    l_Player->TeleportTo(l_Garrison->GetGarrisonSiteLevelEntry()->MapID, l_X, l_Y, l_Z, l_O);
                }
            }

            /// SpellScript/AuraScript interface base
            /// these functions are safe to override, see notes below for usage instructions
            ///
            /// Function in which handler functions are registered, must be implemented in script
            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_garrison_hearthstone_SpellScript::HandleCheckCast);
                OnEffectHit += SpellEffectFn(spell_garrison_hearthstone_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        /// Should return a fully valid SpellScript pointer.
        SpellScript * GetSpellScript() const
        {
            return new spell_garrison_hearthstone_SpellScript();
        }

};


void AddSC_Garrison()
{
    new PlayerScript_Garrison();
    new spell_garrison_hearthstone();
}
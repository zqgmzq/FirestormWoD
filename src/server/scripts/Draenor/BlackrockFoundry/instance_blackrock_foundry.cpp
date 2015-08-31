////////////////////////////////////////////////////////////////////////////////
///
///  MILLENIUM-STUDIO
///  Copyright 2015 Millenium-studio SARL
///  All Rights Reserved.
///
////////////////////////////////////////////////////////////////////////////////

# include "blackrock_foundry.hpp"

DoorData const g_DoorData[] =
{
    { 0, 0, DoorType::DOOR_TYPE_ROOM, BoundaryType::BOUNDARY_NONE } ///< End
};

class instance_blackrock_foundry : public InstanceMapScript
{
    public:
        instance_blackrock_foundry() : InstanceMapScript("instance_blackrock_foundry", 1228) { }

        struct instance_blackrock_foundryMapScript : public InstanceScript
        {
            instance_blackrock_foundryMapScript(Map* p_Map) : InstanceScript(p_Map) { }

            void Initialize() override
            {
                SetBossNumber(0);

                LoadDoorData(g_DoorData);

                instance->SetObjectVisibility(300.0f);
            }

            void OnCreatureCreate(Creature* p_Creature) override
            {
                switch (p_Creature->GetEntry())
                {
                    default:
                        break;
                }
            }

            void OnCreatureRemove(Creature* p_Creature) override
            {
                switch (p_Creature->GetEntry())
                {
                    default:
                        break;
                }
            }

            void OnGameObjectCreate(GameObject* p_GameObject) override
            {
                switch (p_GameObject->GetEntry())
                {
                    default:
                        break;
                }
            }

            void OnGameObjectRemove(GameObject* p_GameObject) override
            {
                switch (p_GameObject->GetEntry())
                {
                    default:
                        break;
                }
            }

            bool SetBossState(uint32 p_BossID, EncounterState p_State) override
            {
                if (!InstanceScript::SetBossState(p_BossID, p_State))
                    return false;

                switch (p_BossID)
                {
                    default:
                        break;
                }

                return true;
            }

            void SetData(uint32 p_Type, uint32 p_Data) override
            {
                switch (p_Type)
                {
                    default:
                        break;
                }
            }

            uint32 GetData(uint32 p_Type) override
            {
                switch (p_Type)
                {
                    default:
                        return 0;
                }
            }

            uint64 GetData64(uint32 p_Type) override
            {
                switch (p_Type)
                {
                    default:
                        break;
                }

                return 0;
            }

            bool CheckRequiredBosses(uint32 p_BossID, Player const* p_Player = nullptr) const override
            {
                if (!InstanceScript::CheckRequiredBosses(p_BossID, p_Player))
                    return false;

                switch (p_BossID)
                {
                    default:
                        break;
                }

                return true;
            }

            void FillInitialWorldStates(ByteBuffer& p_Buffer) override
            {
            }

            void OnPlayerEnter(Player* p_Player) override
            {
                InstanceScript::OnPlayerEnter(p_Player);
            }

            void OnPlayerExit(Player* p_Player) override
            {
                InstanceScript::OnPlayerExit(p_Player);
            }

            void SendUpdateWorldState(uint32 p_Field, uint32 p_Value)
            {
                Map::PlayerList const& l_Players = instance->GetPlayers();
                for (Map::PlayerList::const_iterator l_Iter = l_Players.begin(); l_Iter != l_Players.end(); ++l_Iter)
                {
                    if (Player* l_Player = l_Iter->getSource())
                        l_Player->SendUpdateWorldState(p_Field, p_Value);
                }
            }

            void PlaySceneForPlayers(Position const p_Pos, uint32 p_ScenePackageID)
            {
                Map::PlayerList const& l_Players = instance->GetPlayers();
                for (Map::PlayerList::const_iterator l_Iter = l_Players.begin(); l_Iter != l_Players.end(); ++l_Iter)
                {
                    if (Player* l_Player = l_Iter->getSource())
                        l_Player->PlayStandaloneScene(p_ScenePackageID, 16, p_Pos);
                }
            }
        };

        InstanceScript* GetInstanceScript(InstanceMap* p_Map) const override
        {
            return new instance_blackrock_foundryMapScript(p_Map);
        }
};

void AddSC_instance_blackrock_foundry()
{

}
// fix_leviroth_questid_11626
// Quest: The Emissary (El Emisario)
// ID: 11626
// Fixer: Leuan
// Line to modify: 3121 - 3164

class spell_item_impale_leviroth : public SpellScript
{
    PrepareSpellScript(spell_item_impale_leviroth);

    bool Validate(SpellInfo const* /*spell*/) override
    {
        if (!sObjectMgr->GetCreatureTemplate(NPC_LEVIROTH))
            return false;
        return true;
    }

    void HandleDummy(SpellEffIndex /* effIndex */)
    {
        if (Creature* target = GetHitCreature())
        {
            if (target->GetEntry() == NPC_LEVIROTH && target->HealthAbovePct(94))
            {
                // Reduce the target's health to a low value (e.g., 3.14%)
                int32 newHealth = target->GetMaxHealth() * 0.0314f;
                target->SetHealth(newHealth);

                // Here is supposed to be the cast-spell code, but i removed it to fix the quest.
                // Also, please for safety, remove spell_gen_default_count_pct_from_max_hp from spell_script_names database, WHERE ID = 49882

                // Modify weapon damage if needed (optional)
                target->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, 150);
                target->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, 200);

                // Optional: Lower the damage requirements for players
                target->LowerPlayerDamageReq(target->GetMaxHealth());
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_item_impale_leviroth::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

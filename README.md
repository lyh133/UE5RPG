# Unreal-Engine-RPG
## Table of Contents

- [Overview](#overview)
  - [Currently Implemented](#currently-implemented)
  - [Todo](#todo)
- [Animation System](#animation-system)
  - [Advanced Locomotion System](#advanced-locomotion-system)
  - [Foot and Hand IK](#foot-and-hand-ik)
  - [Running Into Wall Detection](#running-into-wall-detection)
  - [Facial Expression](#facial-expression)
- [Hit Reaction and Gore System](#hit-reaction-and-gore-system)
  - [Hit Reaction](#hit-reaction)
  - [Procedural Mesh Destruction](#procedural-mesh-destruction)
- [Gameplay](#gameplay)
  - [Architecture](#architecture)
  - [Combat System](#combat-system)
  - [Abilities](#abilities)
  - [Weapon](#weapon)
  - [Damage Calculation](#damage-calculation)
  - [AI](#ai)
- [Demos](#demos)
  - [My League of Legends In UE](#my-league-of-legends-In-UE)
  - [QQ Speed](#qq-speed)

## Overview
My solo game project prototype and modular gameplay framework built in Unreal Engine 5 using C++ and Blueprints.

### Currently Implemented

- Advanced locomotion and animation systems
- Gameplay Ability System integration
- Melee, weapon and projectile abilities
- Attribute and damage calculation systems
- Directional hit reactions and stance breaking
- StateTree enemy AI
- Data-driven weapons and abilities
- Procedural mesh damage and injury rendering

### Todo

- Expanded enemy variaty 
- Add Complex AI behaviours
- Inventory and equipment interface
- Save and load support

## Animation System
- Animation Overlay System for additive animations (Injured,Tired, battle stance)
- Ragdoll System and recovery animation
- Aim Offset
- Look Direction Rotation(Smooth Character Rotation animation towards Look direction)
- Turning Animation when sudden change in locomotion direction
- strafe and non-strafe Locomotion
- 8 Ways smooth start and stop animation
- Additive Leaning when character runs in strafe locomotion
- Wall Detection stopping animation
- Foot and Hand IK 
- 4 directional Hit reaction System with Light,Medium, KnockBack and KnockDown Animation
- Facial Expression morph
### Advanced Locomotion System
walk jog sprint with distance matching, Alternative Foot stoping. Look direction Rotation 

▶️Click Image to Play

[![advanced locomotion system](https://img.youtube.com/vi/Pew4T-PQANg/maxresdefault.jpg)](https://www.youtube.com/watch?v=Pew4T-PQANg)

### Foot and Hand IK
<img width="1612" height="1774" alt="Screenshot 2025-11-27 175044" src="https://github.com/user-attachments/assets/b729262d-5fb1-40f3-b220-b8ed01998f80" />

<img width="1457" height="1809" alt="Screenshot 2025-11-27 175650" src="https://github.com/user-attachments/assets/81f8f830-f622-4802-bec6-e4d8d9af19fa" />

### Running Into Wall Detection

<img width="1722" height="1635" alt="Screenshot 2025-11-27 180347" src="https://github.com/user-attachments/assets/c5d47d9b-3949-4001-88ea-7763437f664d" />

### Facial Expression

<img width="1608" height="1312" alt="image" src="https://github.com/user-attachments/assets/e4a480a1-fe20-47c9-9ad8-5bbe9cd7f080" />

## Hit Reaction and Gore System

### Hit Reaction
▶️Click Image to Play
<a href="https://www.bilibili.com/video/BV1AQK86rEGc/">
  <img width="1536" height="1434" alt="image" src="https://github.com/user-attachments/assets/4b517d6e-f484-4804-aa5d-239d04c145cf" />
</a>

### Procedural Mesh Destruction
▶️Click Image to Play
[![Mesh Destruction](https://img.youtube.com/vi/P512S3Jg8M0/maxresdefault.jpg)](https://www.youtube.com/watch?v=P512S3Jg8M0)

Main Character has layers of inner mesh inside the outer skin. The inner meat, inner skeleton and inner organs
the outer skin and inner meat can be destroyed in runtime to create gore effect on the character.
<img width="2830" height="1915" alt="Screenshot 2026-03-04 000511" src="https://github.com/user-attachments/assets/ea099e2d-541c-426c-b55d-36a90584431d" />
<img width="2237" height="1947" alt="tn5" src="https://github.com/user-attachments/assets/996703f6-c3f6-4912-b9a8-02d06d19d0a7" />

Procedual mesh painting is implemented using render targets to unwrap mesh texture from 3D space into UV space before applying sphere mask.
this creates a unwrapped texture with holes of hit location. this can be lerped with injury texture to paint blood or manipulate the mesh world offset to create holes in the mesh. 
different shape of injury(claw mark) can also be painted by multipliying sphere mask with claw mark mask
<img width="1558" height="1234" alt="Screenshot 2026-04-10 155611" src="https://github.com/user-attachments/assets/ddef8eae-4fcb-4a17-ae18-2bb029beb7d0" />
<img width="1313" height="1444" alt="Screenshot 2026-04-10 155535" src="https://github.com/user-attachments/assets/0917affc-a775-4507-b391-390a10adaa37" />

## Gameplay

### Architecture

The project is structured around reusable C++ components, interfaces and Data Assets.

- The Ability System Component manages attributes, abilities, Gameplay Effects and Gameplay Tags.
- The Combat Component handles melee traces, weapon traces, damage application and combat targeting.
- The Status Effect Component manages hit reactions, stagger, knockback, knockdown and temporary disabled states.
- Data Assets store ability, projectile, weapon and item configuration.
- Interfaces allow player characters, AI characters, abilities and combat systems to communicate without tightly coupling their classes.
- Blueprint-facing C++ functions allow gameplay properties and visual behaviour to be configured inside the Unreal Editor.

### Combat System
Implemented with UE GAS (GamePlay Ability System),  character has Health,Stamina,Mana,Stance,Physical Defence, Magical Defence, Regeneration Rate, Attack Damage,Ability Power, Attack Force ...
- Each Attack has Force and Stagger Level, reciepient has Stance and poise,
- character with high force will deal larger stance damage to reciepient When stance is rapidly decreased within short time window. reciepient will be stancebroken triggering KnockBack or KnockDown
- Poise means how much incoming interruption you can withstand before being staggered. Stagger Reaction will be based on the Stagger level of attack. small,mid,heavy,knockback,knockdown.
- Debuffs and Buffs handled With Gameplay Effect

### Abilities
  - Data Driven Abilities/Weapon   (UAbilityData, UProjectileDataAsset, UItemDataAsset)
  - Default Melee Ability class, (Weapon Traced Melee Ability, Point Click Target Locked Ability)
  - Default Ranged Ability Class, (Homing Projectile Ability, Non-Homing Projectile Abiltity)
<img width="2176" height="1521" alt="Screenshot 2026-08-04 140034" src="https://github.com/user-attachments/assets/ca03384c-88eb-4114-b3f1-5f64336e8f91" />
  - Sequenced Melee Combo Ability, with combo sequence has different damage ratio and base damage.
 <img width="1885" height="703" alt="image" src="https://github.com/user-attachments/assets/9f2aedda-8afe-4cbf-ab0b-200f051d14d9" />
  - Default Projectile Class with custimisable VFX SFX, collision Box, and Onhit Effect.
  <img width="2152" height="1347" alt="image" src="https://github.com/user-attachments/assets/8a5394b3-1bc0-48c0-b882-6ee03f677610" />
  - Mark system: fully generalized, data-driven FMarkDefinition (apply/detonate GEs, stack-count gating, that supports arbitrary new marks without new C++.
    Each abillity can apply mark or detonate mark with customisable effects
    <img width="1970" height="918" alt="image" src="https://github.com/user-attachments/assets/b3bf2b7e-5e1b-4794-9b46-1579709c5c7c" />


### Weapon
 - Weapon Equip unequip. dynamically add and remove abilities based on weapon equipped.
 - Multiple weapons can be equipped simultaneously across different sockets, each independently traceable per-attack
<img width="2813" height="1793" alt="Screenshot 2026-07-16 083328" src="https://github.com/user-attachments/assets/8bdf2eee-3360-468c-9e9c-eb17b09ae1bc" />
 - Data Driven
<img width="1986" height="1633" alt="image" src="https://github.com/user-attachments/assets/0c1c0120-ff00-49bc-a46e-b17434818617" />


### Damage Calculation
- Damage is calculated through a custom Gameplay Effect Execution Calculation using Unreal Engine's Gameplay Ability System. This allows damage to be processed using the source and target attributes, Gameplay Tags, defensive statistics and values supplied by individual abilities.
- The system currently supports three damage types:
  - Physical Damage, reduced by Physical Defence, 
  - Magical Damage, reduced by Magical Defence
  - True Damage, which ignores defence
- Each ability passes its damage values through SetByCaller Gameplay Tags, allowing different attacks and abilities to dynamically define:
  - Physical damage
  - Magical damage
  - True damage
  - Physical defence penetration
  - Magical defence penetration
  - Percentage defence penetration
  - Stance damage
<img width="1563" height="1605" alt="image" src="https://github.com/user-attachments/assets/c71f9131-922f-4ac8-8c4d-7fc0b7b45805" />



### AI
  - StateTree-based behaviour and state transitions
  - Sight Hearing/Damage perception
  - Team-based hostile target filtering
  - Target acquisition and target-loss handling
  - Enemy attacks use the same Gameplay Ability System and combat components as the player. This allows AI-controlled characters to use abilities, apply damage, consume attributes and trigger status effects through the same reusable gameplay framework.
  - The StateTree structure is designed to support additional combat behaviours such as attack combinations, lunging attacks, grabbing the player, defensive reactions and different decisions based on distance, cooldowns and character state.

## Demos

### My League of Legends In UE
  - My League of Legends.I made Minion and Turret AI and Animation. Turrets mesh is destructable using chaos destruction. Made Lux Abilities Q W E R
  - ▶️ **Click the image to play the video**
<a href="https://www.bilibili.com/video/BV1s8KM6jELY/">
<img width="2726" height="1854" alt="Screenshot 2026-07-03 231830" src="https://github.com/user-attachments/assets/931e0d6e-1209-4c3e-8012-398cb64f80c4" />
</a>

### QQ Speed
  - QQ Speed was a popular racing gaming back in my childhood so I remade it in UE
  - ▶️ **Click the image to play the video**

<a href="https://www.bilibili.com/video/BV1ZvjV6CEQ7">
<img width="2909" height="1734" alt="Screenshot 2026-06-16 203918" src="https://github.com/user-attachments/assets/65fc9626-7e57-48b0-9861-09c7841ea64d" />
</a>

Notes:
when exporting morph from DAZ to Unreal:
morph character in daz must be in base resolution, must remove all components(eyes,eye brows, mouth)

when using render capture to capture hit location, must edit showflags to disable atmosphere and other effects

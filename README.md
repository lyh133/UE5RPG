# Unreal-Engine-RPG
## Table of Contents
- [Overview](#overview)
- [Animation System](#player)
  - [8 Ways strafe movement](#Strafe-Locomotion)
  - [Free camera locomotion](#Free-camera-locomotion)
  - [Ragdoll Animation](#Ragdoll-Animation)
- [AI](#ai)
- [Abilities](#abilities)

## Overview
My Action RPG Project with Unreal Engine. with characters imported from Dazstudio using Genesis 9 Skeleton with fully modular clothing and 8K resolution Mesh.
works with Dazstudio Morph target to bring facial animation to character. 

## Animation System
- Animation Overlay System for additive animations (Injured,Tired, battle stance)
- Ragdoll System and recovery animation
- Aim Offset(characters upperbody moves with mouse)
- Look Direction Rotation(Smooth Character Rotation animation towards Look direction)
- Turning Animation when sudden change in locomotion direction
- strafe and non-strafe Locomotion
- 8 Ways smooth start and stop animation
- Additive Leaning when character runs in strafe locomotion
- Wall Detection stopping animation
- Foot and Hand IK for realistic foot placement on inclined surface 
- 4 directional Hit reaction System with Light,Medium, KnockBack and KnockDown Animation
### Strafe Locomotion  
walk jog sprint implemented with distance matching

▶️Click to Play

[![8 Ways strafe movement](https://img.youtube.com/vi/iFtPwbyxWeM/maxresdefault.jpg)](https://www.youtube.com/watch?v=iFtPwbyxWeM)


<img width="500" height="500" alt="image" src="https://github.com/user-attachments/assets/40ce59b0-8cd2-4e69-a46b-2a402be2697b" />

### free camera locomotion

implemented with turning animation, start and stop

▶️Click to Play

[![free camera locomotion](https://img.youtube.com/vi/_K6sNZNwI1U/maxresdefault.jpg)](https://www.youtube.com/watch?v=_K6sNZNwI1U)

### Ragdoll Animation

▶️Click to Play

[![Ragdoll Animation](https://img.youtube.com/vi/DfBtOjgbt3k/maxresdefault.jpg)](https://www.youtube.com/watch?v=DfBtOjgbt3k)

### Foot and Hand IK
<img width="1612" height="1774" alt="Screenshot 2025-11-27 175044" src="https://github.com/user-attachments/assets/b729262d-5fb1-40f3-b220-b8ed01998f80" />

<img width="1457" height="1809" alt="Screenshot 2025-11-27 175650" src="https://github.com/user-attachments/assets/81f8f830-f622-4802-bec6-e4d8d9af19fa" />

### Running Into Wall Detection

<img width="1722" height="1635" alt="Screenshot 2025-11-27 180347" src="https://github.com/user-attachments/assets/c5d47d9b-3949-4001-88ea-7763437f664d" />


### Combat System
Implemented with Unreal Engine GAS(GamePlay Ability System),  character has Health,Stamina,Mana,Stance,Physical Defence, Magical Defence, Regeneration Rate, Attack Damage,Ability Power, Attack Force
- Debuffs are applied to injured and tired character reducing regeneration rate and increases damage recieved.
- character with high force will deal larger stance damage to reciepient, When stance is rapidly decreased within short time window. reciepient will be stancebroken triggering KnockBack or KnockDown
  
## AI
Details...

## Abilities
Details...

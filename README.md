# Unreal-Engine-RPG
## Table of Contents
- [Overview](#overview)
- [Animation System](#animation-system)
  - [8 Ways strafe movement](#8-ways-Strafe-Locomotion)
  - [Free camera locomotion](#Free-camera-locomotion)
  - [Ragdoll Animation](#Ragdoll-Animation)
- [Gore System](#gore-system)
  - [Procedural Mesh Destruction](#procedural-mesh-destruction)
- [Gameplay](#gameplay)
  - [Combat System](#combat-system)
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
walk jog sprint with distance matching, Alternative Foot stoping. Look direction Rotation 

▶️Click to Play

[![8 Ways strafe Locomotion](https://img.youtube.com/vi/t9RhUe8Mw7E/maxresdefault.jpg)](https://www.youtube.com/watch?v=t9RhUe8Mw7E)


<img width="500" height="500" alt="image" src="https://github.com/user-attachments/assets/40ce59b0-8cd2-4e69-a46b-2a402be2697b" />

### free camera locomotion

implemented with turning animation, start and stop

▶️Click to Play

[![Directional Hit Reaction](https://img.youtube.com/vi/_K6sNZNwI1U/maxresdefault.jpg)](https://www.youtube.com/watch?v=_K6sNZNwI1U)

### Directional Hit Reaction 
has light,medium,knockback and knockdown severity

▶️Click to Play

[![free camera locomotion](https://img.youtube.com/vi/vHyyhOJNtnQ/maxresdefault.jpg)](https://www.youtube.com/watch?v=vHyyhOJNtnQ)

▶️Click to Play

[![free camera locomotion](images/tn1.png)](https://www.bilibili.com/video/BV1ccZKBFEAy/)

### Ragdoll Animation

▶️Click to Play

[![Ragdoll Animation](https://img.youtube.com/vi/DfBtOjgbt3k/maxresdefault.jpg)](https://www.youtube.com/watch?v=DfBtOjgbt3k)

### Foot and Hand IK
<img width="1612" height="1774" alt="Screenshot 2025-11-27 175044" src="https://github.com/user-attachments/assets/b729262d-5fb1-40f3-b220-b8ed01998f80" />

<img width="1457" height="1809" alt="Screenshot 2025-11-27 175650" src="https://github.com/user-attachments/assets/81f8f830-f622-4802-bec6-e4d8d9af19fa" />

### Running Into Wall Detection

<img width="1722" height="1635" alt="Screenshot 2025-11-27 180347" src="https://github.com/user-attachments/assets/c5d47d9b-3949-4001-88ea-7763437f664d" />

## Gore System

### Procedural Mesh Destruction

▶️Click to Play

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

### Combat System
Implemented with Unreal Engine GAS(GamePlay Ability System),  character has Health,Stamina,Mana,Stance,Physical Defence, Magical Defence, Regeneration Rate, Attack Damage,Ability Power, Attack Force
- Debuffs are applied to injured and tired character reducing regeneration rate and increases damage recieved.
- character with high force will deal larger stance damage to reciepient, When stance is rapidly decreased within short time window. reciepient will be stancebroken triggering KnockBack or KnockDown
  
▶️Click to Play

[![free camera locomotion](images/tn3.png)](https://www.bilibili.com/video/BV1VuZsBiEM9/)
### AI
Details...

### Abilities
Details...

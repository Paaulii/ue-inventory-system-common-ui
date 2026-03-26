# Inventory System 🎒
###### Last update: 26.03.2026
An inventory system implements MVVM pattern and was created using Common UI, it handles navigation for both gamepad and keyboard/mouse input.  Inventory System uses Gameplay Ability System for making actions on items, such as consume, equip.
Gamepad                    |  Keyboard                  
:-------------------------:|:-------------------------:
<img width="1909" height="987" alt="image" src="https://github.com/user-attachments/assets/ac17e178-2a88-4a4d-a042-e827925d3a59" /> | <img width="1907" height="988" alt="image" src="https://github.com/user-attachments/assets/70d67d05-835f-4e27-8f3d-4ad35192f6d1" /> 

The project currently is **still in progress** but it has already implemented several features such as:
- Easy to extend and mantain data array with item's definitions. This is the place where we can specify what Gameplay Effects item has.
<img width="1910" height="840" alt="image" src="https://github.com/user-attachments/assets/e37ec1b8-2484-496b-a6d8-ed9a040d7011" />

- Displaying items per category

Consumable                 |  Weapons                  |  Armor
:-------------------------:|:-------------------------:|:-------------------------:
<img width="1907" height="988" alt="image" src="https://github.com/user-attachments/assets/70d67d05-835f-4e27-8f3d-4ad35192f6d1" />  | <img width="1912" height="986" alt="image" src="https://github.com/user-attachments/assets/2c72ef20-8d9c-458a-affe-742b1b6a2bcc" /> | <img width="1908" height="990" alt="image" src="https://github.com/user-attachments/assets/b711002b-43fb-4e64-baa2-4a116fe80a3d" />

- Consuming items

Before                     |  Confirmation window      |  After
:-------------------------:|:-------------------------:|:-------------------------:
<img width="1915" height="989" alt="image" src="https://github.com/user-attachments/assets/da5386bd-67f2-4734-b9df-62acdfec530b" /> | <img width="1915" height="996" alt="image" src="https://github.com/user-attachments/assets/de1d53b4-fd77-44b6-a414-9f8d453f9fbd" /> | <img width="1913" height="992" alt="image" src="https://github.com/user-attachments/assets/326a277d-d6ea-487b-ba39-bbf71dfe172c" />

- Equipping items - Player's stats change depending on equipped items

Before                     |  After
:-------------------------:|:-------------------------:
<img width="1913" height="994" alt="image" src="https://github.com/user-attachments/assets/e6ff27d7-bdbf-4fbf-a7cb-e7848f16ecb7" /> | <img width="1916" height="990" alt="image" src="https://github.com/user-attachments/assets/6c506721-bef3-4952-af1f-66b7275439e1" />

- Different action buttons depending on item's type and state

Consume                    |  Equip                    |  Unequip 
:-------------------------:|:-------------------------:|:-------------------------:
<img width="655" height="563" alt="image" src="https://github.com/user-attachments/assets/58f945b1-e1de-4456-ad01-9d6e888fa627" /> | <img width="648" height="544" alt="image" src="https://github.com/user-attachments/assets/f99aca3a-4a70-486e-abc5-cfb87d04bd89" /> | <img width="642" height="557" alt="image" src="https://github.com/user-attachments/assets/efcbfc44-e559-4c86-8d5f-f8da9de148d3" />

- Confirmation widgets
<img width="1915" height="996" alt="image" src="https://github.com/user-attachments/assets/a80511f0-79cb-4d9d-a3cd-a821a7c8c1b6" />

### Plans for the future:
- Update characters currently equipped items
- Add camera preview in character's details window
- Support dropping items
- Extend confirmation widget to have a slider to allow player to choose how many consumable items want to consume or how many items want to drop.
- Create Pick-up notification widget.
- Create popup error message when consuming isn't available - when player has max health or mana.
- Add lock image on items that have higher level than player's.

### Used assets in game:

#### GUI assets:
- 50 Free Stylized Icons - [https://assetstore.unity.com/packages/2d/gui/icons/2d-casual-ui-hd-82080#asset_quality](https://assetstore.unity.com/packages/2d/50-free-stylized-icons-307753?srsltid=AfmBOoqv7bltzKUTCW7nOJrxS7JLfQMwV2Ggd7GKm2n4wbyVVTCrZ8oE)
 
- Free Icon Pack for Unity & Unreal – 1500+ Input Icons for Game UI - JulioCacko - [https://assetstore.unity.com/packages/3d/props/simple-gems-ultimate-animated-customizable-pack-73764#reviews](https://juliocacko.itch.io/free-input-prompts)

- Pixel RPG Icons - [https://assetstore.unity.com/packages/vfx/particles/cartoon-fx-remaster-free-109565](https://kickpixel.itch.io/50fantasyicons)


#### Fonts:
- Caslon Antique is licensed under the 1001Fonts Free For Commercial Use License (FFC) - [https://www.1001fonts.com/caslon-antique-font.html#license](https://www.1001fonts.com/caslon-antique-font.html)

#### Plugins:
- MVVM
- Common UI
# Inventory System 🎒
###### Last update: 14.05.2026
An inventory system implements MVVM pattern and was created using Common UI, it handles navigation for both gamepad and keyboard/mouse input.  Inventory System uses Gameplay Ability System for making actions on items, such as consume, equip.

Gamepad                    |  Keyboard                  
:-------------------------:|:-------------------------:
<img width="1915" height="985" alt="image" src="https://github.com/user-attachments/assets/531fd717-5103-45e3-942c-445bd34d0d83" /> | <img width="1913" height="989" alt="image" src="https://github.com/user-attachments/assets/d2b4f85f-1069-4fb6-90e2-603e8f5ce7fc" />

Features:
- Easy to extend and mantain data array with item's definitions. This is the place where we can specify what Gameplay Effects item has.
<img width="1325" height="842" alt="image" src="https://github.com/user-attachments/assets/08b51a03-e8c6-4c98-a66c-28d4182829d4" />

- Displaying items per category

Consumable                 |  Weapons                  |  Armor
:-------------------------:|:-------------------------:|:-------------------------:
<img width="1913" height="989" alt="image" src="https://github.com/user-attachments/assets/d2b4f85f-1069-4fb6-90e2-603e8f5ce7fc" /> | <img width="1915" height="988" alt="image" src="https://github.com/user-attachments/assets/4554382e-4178-4d9f-87d8-45435fd3a046" /> | <img width="1914" height="988" alt="image" src="https://github.com/user-attachments/assets/92a93f34-3b27-4c25-a738-f4c78353bc94" />

- Pagination

First page                 |  Second Page               
:-------------------------:|:-------------------------:
<img width="1913" height="985" alt="image" src="https://github.com/user-attachments/assets/ef0e2250-8328-4d61-bb7a-5244fdb08eba" /> | <img width="1919" height="974" alt="image" src="https://github.com/user-attachments/assets/1c161ad3-2a18-4bcc-a3f2-c1baea9cbbff" />

- Consuming items

Before                     |  Confirmation window      |  After
:-------------------------:|:-------------------------:|:-------------------------:
<img width="1912" height="991" alt="image" src="https://github.com/user-attachments/assets/df2d4039-bfb7-493c-8fad-077bf2ecfc61" /> | <img width="1913" height="989" alt="image" src="https://github.com/user-attachments/assets/ab99b7a9-2d55-4be3-ad65-9bedc79c3d77" /> | <img width="1914" height="992" alt="image" src="https://github.com/user-attachments/assets/3bf1ed45-05f2-42d1-ae26-9e7f75edc06c" />

- Equipping items - Player's stats change depending on equipped items

Before                     |  After
:-------------------------:|:-------------------------:
<img width="1914" height="985" alt="image" src="https://github.com/user-attachments/assets/efe6a764-ea53-469e-ad29-1bd78bdf1506" /> | <img width="1912" height="985" alt="image" src="https://github.com/user-attachments/assets/150536c5-d1bc-4186-98a3-3d94b94b3212" />

<img width="1916" height="986" alt="image" src="https://github.com/user-attachments/assets/c97f54a4-a6ae-4e25-9b59-d2e099b6d286" />
 
- Dropping items

Confirmation widget        |  Unequipping dropped item | Spawning item in defined range 
:-------------------------:|:-------------------------:|:-------------------------:
<img width="1914" height="979" alt="image" src="https://github.com/user-attachments/assets/68ddef69-7608-4846-abc1-c1658fc43f04" /> | <img width="1913" height="985" alt="image" src="https://github.com/user-attachments/assets/c6940b4b-d5ad-43e0-b87c-91bc40b31805" /> | <img width="1911" height="986" alt="image" src="https://github.com/user-attachments/assets/7e2a70c7-cf3b-4b98-966b-25117da811a6" />

- Selling items

Before                     |  Confirmation widget      | After
:-------------------------:|:-------------------------:|:-------------------------:
<img width="1909" height="989" alt="image" src="https://github.com/user-attachments/assets/0c66dc99-f2e0-4d2b-ad9a-506c424fda97" /> | <img width="1915" height="982" alt="image" src="https://github.com/user-attachments/assets/399e3998-c7c4-43e2-91ba-536dabd793d2" /> | <img width="1914" height="993" alt="image" src="https://github.com/user-attachments/assets/0a89f2a7-a25c-48fb-b93e-611b31c60f68" />

- Different action buttons depending on item's type and state

Consume                    |  Equip                    |  Unequip 
:-------------------------:|:-------------------------:|:-------------------------:
<img width="711" height="666" alt="image" src="https://github.com/user-attachments/assets/402f589b-563f-41b0-aeca-e6c85525edfb" /> | <img width="669" height="694" alt="image" src="https://github.com/user-attachments/assets/bd58e46a-6ad7-427b-80d5-de6c316ad13a" /> | <img width="670" height="684" alt="image" src="https://github.com/user-attachments/assets/b1f9120d-a83c-4fe9-bcc9-2811db4e7261" />

- Confirmation widgets

Single item action         |  Multiple item action  
:-------------------------:|:-------------------------:
<img width="1909" height="985" alt="image" src="https://github.com/user-attachments/assets/7228adb8-d99f-4c08-8082-7da6dd22bf27" /> |  <img width="1914" height="985" alt="image" src="https://github.com/user-attachments/assets/f2866257-80d5-48cd-8741-f63909c189d0" />

- Pickup popup when hovering over an item
<img width="1914" height="990" alt="image" src="https://github.com/user-attachments/assets/d5c398c3-8a8e-4ef4-a130-6208751e36e9" />

- Pick-up notification system

Single item notification   | Multiple item notification
:-------------------------:|:-------------------------:
<img width="452" height="160" alt="20260514-0947-41 2120515" src="https://github.com/user-attachments/assets/f2a5f31d-2fb3-4628-a8b9-9067e511da81" /> |<img width="452" height="160" alt="20260514-0949-21 0821725" src="https://github.com/user-attachments/assets/8054d11a-f57a-43f8-ae99-9bd7a1831fa3" />

- Pick-up notification system - configurable max number of notifications - notification's queue system

https://github.com/user-attachments/assets/d29bede7-13a1-4830-9324-d549516462c4

### Inspiration:
I took an inspiration for UI layout and separation of data stored in ViewModels from Irene Zanon, presented in Handling UI navigation with MVVM and Common Activatable Widgets tutorial : https://dev.epicgames.com/community/learning/tutorials/ep4k/unreal-engine-handling-ui-navigation-with-mvvm-and-common-activatable-widgets 

### Used assets:

#### 3D assets:
- Viking Helmet - https://www.fab.com/listings/a3891f55-339a-47ad-b75c-b97c792ab579
- Magic Potion Free game-ready 3D asset - https://fab.com/s/1b428cca34bf
- High-res Potion Bottles - https://cadelegeberg.itch.io/free-potion-bottles-transparent-in-hand-painted-style
- KayKit : Fantasy Weapons Bits - https://kaylousberg.itch.io/fantasy-weapons-bits
- 5 Piece Platemail - MetaHuman (rigged) by DevonLux is licensed under Creative Commons Attribution (http://creativecommons.org/licenses/by/4.0/). - https://sketchfab.com/3d-models/5-piece-platemail-metahuman-rigged-d5a36fd5d69640b29bb7e92f72f61608

#### GUI assets:
- 50 Free Stylized Icons - [https://assetstore.unity.com/packages/2d/gui/icons/2d-casual-ui-hd-82080#asset_quality](https://assetstore.unity.com/packages/2d/50-free-stylized-icons-307753?srsltid=AfmBOoqv7bltzKUTCW7nOJrxS7JLfQMwV2Ggd7GKm2n4wbyVVTCrZ8oE)
 
- Free Icon Pack for Unity & Unreal – 1500+ Input Icons for Game UI - JulioCacko - [https://assetstore.unity.com/packages/3d/props/simple-gems-ultimate-animated-customizable-pack-73764#reviews](https://juliocacko.itch.io/free-input-prompts)

- Free Icon Pack by @gvesster - https://gvesster.itch.io/free-icon-pack
 
- GUI Parts - PONETI - https://www.fab.com/pl/listings/695e149d-93e3-42bb-b021-4f1bbf6eac2a

- Sprout Lands UI Pack- https://cupnooble.itch.io/sprout-lands-ui-pack

#### Fonts:
- Caslon Antique is licensed under the 1001Fonts Free For Commercial Use License (FFC) - [https://www.1001fonts.com/caslon-antique-font.html#license](https://www.1001fonts.com/caslon-antique-font.html)

#### Plugins:
- MVVM
- Common UI
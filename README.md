# Inventory System 🎒
###### Last update: 02.04.2026
An inventory system implements MVVM pattern and was created using Common UI, it handles navigation for both gamepad and keyboard/mouse input.  Inventory System uses Gameplay Ability System for making actions on items, such as consume, equip.
Gamepad                    |  Keyboard                  
:-------------------------:|:-------------------------:
<img width="1901" height="989" alt="image" src="https://github.com/user-attachments/assets/37f98d8c-7ce1-4927-98c9-3b78c57bcdf5" /> | <img width="1902" height="987" alt="image" src="https://github.com/user-attachments/assets/92f6265e-ccfe-42d2-b070-1cca64a2a0fb" />

The project currently is **still in progress** but it has already implemented several features such as:
- Easy to extend and mantain data array with item's definitions. This is the place where we can specify what Gameplay Effects item has.
<img width="1910" height="840" alt="image" src="https://github.com/user-attachments/assets/e37ec1b8-2484-496b-a6d8-ed9a040d7011" />

- Displaying items per category

Consumable                 |  Weapons                  |  Armor
:-------------------------:|:-------------------------:|:-------------------------:
<img width="1902" height="987" alt="image" src="https://github.com/user-attachments/assets/92f6265e-ccfe-42d2-b070-1cca64a2a0fb" />  | <img width="1908" height="985" alt="image" src="https://github.com/user-attachments/assets/d1637af2-6e63-4309-8ebf-79fa4d6fa296" /> | <img width="1911" height="980" alt="image" src="https://github.com/user-attachments/assets/c132c4af-5c4b-4e47-8fd6-a9df7087ddfb" />

- Pagination

⚠️ Ability to extend player's inventory size in progress
First page                 |  Second Page               
:-------------------------:|:-------------------------:
d<img width="1910" height="984" alt="image" src="https://github.com/user-attachments/assets/8c81b5fa-2a2d-4f32-947d-bd247749884b" /> | <img width="1905" height="993" alt="image" src="https://github.com/user-attachments/assets/781b168d-6090-4ca1-9cff-f850f9863582" />

- Consuming items

⚠️ Selecting item's amount to consume in progress
Before                     |  Confirmation window      |  After
:-------------------------:|:-------------------------:|:-------------------------:
<img width="1915" height="989" alt="image" src="https://github.com/user-attachments/assets/da5386bd-67f2-4734-b9df-62acdfec530b" /> | <img width="1909" height="984" alt="image" src="https://github.com/user-attachments/assets/e79d8f0b-5d82-4aef-8d33-6e28457d155c" /> | <img width="1913" height="992" alt="image" src="https://github.com/user-attachments/assets/326a277d-d6ea-487b-ba39-bbf71dfe172c" />

- Equipping items - Player's stats change depending on equipped items

Before                     |  After
:-------------------------:|:-------------------------:
<img width="1905" height="985" alt="image" src="https://github.com/user-attachments/assets/45e02765-5e5b-4d92-bdfc-53c92d0c8528" /> | <img width="1899" height="985" alt="image" src="https://github.com/user-attachments/assets/1358cb55-1d27-45fb-b564-cc5cb7832c93" />

 <img width="1903" height="988" alt="image" src="https://github.com/user-attachments/assets/92bf5410-71d8-4ccb-985d-94d0a6aadd29" />
 
- Dropping items with defined range

⚠️ Selecting item's amount to drop in progress

Confirmation widget        |  Unequipping dropped item | Spawning item in defined range 
:-------------------------:|:-------------------------:|:-------------------------:
<img width="1908" height="987" alt="image" src="https://github.com/user-attachments/assets/d7584cdc-70f9-4322-8e3d-cff789c903e5" /> | <img width="1912" height="989" alt="image" src="https://github.com/user-attachments/assets/e65c4b10-b214-4cd9-8dae-a01d79bc97ae" /> | <img width="1908" height="987" alt="image" src="https://github.com/user-attachments/assets/7a85f5c0-e578-41ed-9a68-df4ab7aad4ad" />

- Selling items

⚠️ Selecting item's amount to sell in progress
Before                     |  Confirmation widget      | After
:-------------------------:|:-------------------------:|:-------------------------:
<img width="1914" height="991" alt="image" src="https://github.com/user-attachments/assets/50f4fb20-8397-4a97-a854-5752cfa80606" /> | <img width="1910" height="990" alt="image" src="https://github.com/user-attachments/assets/815199c4-f84c-4ddb-a07c-a1d4193c15aa" /> | <img width="1908" height="991" alt="image" src="https://github.com/user-attachments/assets/33ede16f-a704-4978-ae20-3b1bdbcf14a9" />

- Different action buttons depending on item's type and state

Consume                    |  Equip                    |  Unequip 
:-------------------------:|:-------------------------:|:-------------------------:
<img width="655" height="563" alt="image" src="https://github.com/user-attachments/assets/58f945b1-e1de-4456-ad01-9d6e888fa627" /> | <img width="648" height="544" alt="image" src="https://github.com/user-attachments/assets/f99aca3a-4a70-486e-abc5-cfb87d04bd89" /> | <img width="642" height="557" alt="image" src="https://github.com/user-attachments/assets/efcbfc44-e559-4c86-8d5f-f8da9de148d3" />

- Confirmation widgets
<img width="1909" height="984" alt="image" src="https://github.com/user-attachments/assets/e79d8f0b-5d82-4aef-8d33-6e28457d155c" />

### Plans for the future:
- Extend confirmation widget to have a slider to allow player to choose how many consumable items want to consume or how many items want to drop.
- Create Pick-up notification widget.
- Create popup error message when consuming isn't available - when player has max health or mana.
- Add lock image on items that have higher level than player's.
- Move UI System onto separate Github repository and add it as a repository module to this repository.

### Inspiration:
I took an inspiration for UI layout and separation of data stored in ViewModels from Irene Zanon, presented in Handling UI navigation with MVVM and Common Activatable Widgets tutorial : https://dev.epicgames.com/community/learning/tutorials/ep4k/unreal-engine-handling-ui-navigation-with-mvvm-and-common-activatable-widgets 

### Used assets:
#### GUI assets:
- 50 Free Stylized Icons - [https://assetstore.unity.com/packages/2d/gui/icons/2d-casual-ui-hd-82080#asset_quality](https://assetstore.unity.com/packages/2d/50-free-stylized-icons-307753?srsltid=AfmBOoqv7bltzKUTCW7nOJrxS7JLfQMwV2Ggd7GKm2n4wbyVVTCrZ8oE)
 
- Free Icon Pack for Unity & Unreal – 1500+ Input Icons for Game UI - JulioCacko - [https://assetstore.unity.com/packages/3d/props/simple-gems-ultimate-animated-customizable-pack-73764#reviews](https://juliocacko.itch.io/free-input-prompts)

- Pixel RPG Icons - [https://assetstore.unity.com/packages/vfx/particles/cartoon-fx-remaster-free-109565](https://kickpixel.itch.io/50fantasyicons)


#### Fonts:
- Caslon Antique is licensed under the 1001Fonts Free For Commercial Use License (FFC) - [https://www.1001fonts.com/caslon-antique-font.html#license](https://www.1001fonts.com/caslon-antique-font.html)

#### Plugins:
- MVVM
- Common UI
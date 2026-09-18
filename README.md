# House of the Veil

A narrative first-person mystery/horror game with puzzle elements, inspired by the true events of the 1858 Bradford sweets poisoning in Victorian England.

![Entrance Hall](docs/images/entrance-hall.png)

## Overview

| | |
|---|---|
| **Genre** | Narrative First-Person Mystery / Horror |
| **Platform** | PC (Windows) |
| **Engine** | Unreal Engine 5.5.4 |
| **Target audience** | 18+ |
| **Development** | Diploma Games Programming — Creative Studio 1 |

## High Concept

The player finds themselves in the abandoned estate of the Edwards family — a lonely, oppressive place that shrouds its past like a veil. By exploring its rooms and solving its puzzles, that veil lifts piece by piece, revealing a tragic story of guilt and loss.

House of the Veil deliberately favors atmosphere over jumpscares, and emotional depth over gore. At its core, it tells the story of thirteen-year-old Amelia, who returns to her family's estate in a liminal, in-between world. The house is a manifestation of her guilt over believing she is responsible for her family's death, and of her desperate longing for reunion — a longing expressed through collecting dolls representing her deceased family members and bringing them together in a dollhouse.

## Story

Told from the perspective of 13-year-old Amelia Edwards, a girl from the upper-middle class living with her family in Bradford, Yorkshire during the Victorian era. The story unfolds between October 31 and November 4, 1858 — the days in which her entire family dies suddenly and agonizingly on Halloween, followed by Amelia's own final, lonely days until her death on November 4, 1858.

The narrative is delivered entirely through environmental storytelling: newspaper articles, farewell letters, and diary entries left behind by the family.

**Family: Edwards**
- Amelia Edwards, 13 (playable character)
- George Edwards, 9 (brother)
- Eleanor Edwards, 36 (mother)
- Winston Edwards, 48 (father)

## Gameplay

### Core Loop

1. Check the **dollhouse** to see which room of the estate is currently unlocked (indicated by a lit window).
2. Find and explore the corresponding room.
3. Solve the room's puzzle to find that family member's doll.
4. Place the doll in the dollhouse — this lights up the next room and unlocks its door.

### Mechanics

- **Character movement** — WASD + mouse look.
- **Pickup items** — objects like the travel light and dolls can be carried and placed.
- **Environmental interaction** — opening doors, reading letters/newspapers, starting puzzles.

### Progression (Play-by-Play)

1. Start the game from the main menu.
2. Find the **father's doll** in the entrance hall and bring it to the dollhouse → unlocks the piano room.
3. Solve the **piano puzzle** → spawns the **mother's doll**.
4. Bring the mother's doll to the dollhouse → unlocks the children's room.
5. Solve the **chess puzzle** → receive the **brother's doll**.
6. Bring the brother's doll to the dollhouse.
7. Sign the guestbook.
8. The main entrance door opens — ending reached.

### Puzzles

- **Piano puzzle** — 88 individually playable keys; the player must replay a note sequence correctly to progress. A correct sequence spawns the mother's doll; an incorrect one resets the puzzle.
- **Chess puzzle** — the player must move chess pieces into their correct positions. Success causes the board to split open, revealing the brother's doll.

### Optional collectibles

Sweets (mint and caramel) are hidden throughout the estate as an optional side activity, unrelated to main story progression. Collected sweets are tracked and shown in the online guestbook.

## Game States

- **Start State** — main menu (visually integrated into the game world as a Victorian door): start game, credits, exit.
- **In-Game State** — free exploration, interaction, reading documents, solving puzzles, collecting and placing dolls. No health system or classic "game over" — progress is driven entirely by puzzle-solving.
- **Pause State** — pause, return to main menu, or quit; gameplay fully halts.
- **End State** — reached once all dolls are placed in the dollhouse. The player can sign the guestbook, view the credits, and return to the main menu.

## Art Direction

The visual style follows a melancholic, oppressive, and atmospherically dense aesthetic. The house looks maintained but abandoned; wealthy but empty; warmly lit but emotionally cold. Tension is built through stillness, emptiness, and subtle unease rather than visible horror.

### Key Assets

- **Dollhouse & dolls** — represent Amelia's family and her longing for reunion.
- **Piano** — every key exists as an individually rotatable static mesh so it can be played.
- **Chessboard & pieces** — pieces are player-movable; the board splits open at its center once the puzzle is solved, revealing George's doll.
- **Travel light & candelabras** — a historical travel candle holder used to light candelabras placed around the house, shaping the house's lighting mood.
- **Sweets & bowl** — two varieties (peppermint and caramel), distributed throughout the house.

## UI

UI is intentionally minimalist to preserve immersion — no permanent HUD.

- **Main menu** — integrated into the game world as a dark Victorian door; the title is rendered in a red, distorted horror font, with clean, legible menu options. Pressing "Play" opens the door directly into the estate.
- **Documents & newspapers** — displayed fullscreen with an aged paper texture and period-accurate typography.
- **Guestbook** — an interactive, page-turning book showing historical entries and online player entries (name + sweets collected).
- **Piano puzzle UI** — a subtle diamond-symbol sequence indicator above the keys shows how many notes must be played correctly; a note button allows replaying the melody; success is confirmed with a brief "Success" message.

## Audio

- **Footsteps** — varied wood footstep sounds, randomized during movement.
- **Piano tones** — sampled recordings of all 88 notes, mapped to their corresponding key.
- **Ambience** — wind through doors and windows, creaking wood, "ghost" footsteps — designed to make the house feel alive.
- **Doors** — open/close/lock/unlock sound effects, randomized across multiple tracks for variance.
- **Chessboard** — wood sounds for placing and sliding pieces.
- **Fire** — sound effect for lighting candles.

## Networking / Online Feature

An old, leather-bound guestbook sits visibly at the estate's entrance, recording the names of every player who has freed their soul and escaped the house. On completion, players can immortalize themselves with their name and the number of sweets they found.

- Online feature connected to a server; shows player name and sweets collected.
- Acts as a social element, making players visible to one another, and adds replay motivation (beating others' sweet counts).
- Requires a secure server connection; possible filters include global, Steam friends list (nice-to-have), and an offline mode with fictional, game-generated entries.
- Each entry displays player name, playtime, sweets found, and departure date, grouped by date under a page title (e.g. "Arrived 19.01.1980").

## Technology

- **Engine:** Unreal Engine 5.5.4 (development) / 5.6.1 (licensing)
- **Platform:** Windows 11
- **Input:** Mouse & keyboard
- **Tools:** JetBrains Rider (student license), Maya (student license)

## Target Audience

Ages roughly 18–40. Rated 18+ due to sensitive themes including death, suicide, and psychological distress. Aimed at players who enjoy puzzles and slow, atmospheric horror with strong story elements.

## Marketing

Planned as a demo release on Steam.

## Licensing & IP

Historical texts referenced (e.g. the *Bradford Observer*, 1858) are in the public domain. Any Marketplace assets used are licensed according to their respective terms.

House of the Veil is an original creative work. The game concept, narrative, characters (e.g. Amelia Edwards), puzzle design, and the composed piano piece used in the piano puzzle are original work by the team. While inspired by the historical Bradford sweets poisoning of 1858, the game is a fictional interpretation — all narrative expansions, character portrayals, and gameplay implementations are the team's own creative contributions.

## Credits

Developed by **Alexandra Erni** and **Yannic Sutter**
Diploma Games Programming, Creative Studio 1 — Zurich, Switzerland

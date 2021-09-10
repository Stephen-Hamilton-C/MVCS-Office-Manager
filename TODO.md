# To-do list

Needed and planned features will be placed into this file.

## [TODO]
- [x] Fix new inspection window appearing for new supply item
- [x] Make a category section for supply items
- [x] Make date picker automatically default to last Thursday
- [x] Dropdowns for new inspection are tiny compared to new cadet dropdowns
- [x] Need tabbing for new inspection window
- [x] Try to put ranks in order in combo boxes
- [x] Alphabetize the names for cadet selection in inspections
- [ ] Add PT score entering
- [x] Add "save before quitting"
- [x] Save as and load functionality
- [x] Add prefixes to UUIDs for different datatypes
- [x] Make a version string in each JSON file and make a converter class that converts the old version to the new version
- [x] Changes made indicator, then make the confirm dialog not appear if no changes were made
- [x] Pass MainWindow to children rather than make it singleton

### QOL
- [ ] Make DataManager automatically open last file if possible
- [x] Make header indicating what category editor is open
- [ ] Remove trailing newline in supply item properties
- [ ] When creating new item, suggest editing an existing item if name already exists
- [x] Remove "back to logo" when selecting the same screen
- [ ] Requisition entry, automatically removes one count from an item
- [x] See if sets exist in C++ or Qt, and store categories in a set
- [ ] Remove context help from windows, or add helps to elements
- [ ] Make DataConverter convert properties so that items don't have the "item_" in the key for each property of an item. It seems redundant to have an array of cadets and for each property of each cadet to start with "cadet_"
- [ ] Turn all the methods with the huge switch statements into constant maps
- [ ] Don't show a comma if there's no first name in cadet display

### Rewrite
**Codebase is becoming unstable and needs a rewrite to accomodate extra features and better understanding of Qt**
- [ ] Fracture MainWindow.cpp
- [ ] Make better implementation of the table view - various fixes will be made simple
- [ ] Fix sorting category being reset on item edit, creation, or deletion
- [ ] Fix rows having whitespace on top and bottom unless it is reloaded twice
- [ ] Fix count being organized by string and not by number (23 is smaller than 3)
- [ ] User configuration, independant of the data JSON. Use this to make persistent columns
- [ ] Make an editor base class and have the editors extend off it
- [ ] Make maps private in DataManager so the items map can be utilized
- [ ] Export as CSV
- [ ] Press enter to edit from table
- [ ] Add full stock count for supply items
	- [ ] maybe replace low count with full count and alert when at 30% stock?
- [ ] Export list of needed supply items

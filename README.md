# Class Manager

A C console program that records each student's ID, name and Korean and English scores, then prints them sorted by a chosen field along with the class average and standard deviation. Menu output, input validation and string checks are split into separate modules by file. A school assignment.

<p>
  <img src="docs/screenshots/screenshot-1.png" width="480" alt="Main menu">
</p>


## How to use

Download from Releases and run it. Type a command after `명령어 :` and press Enter. The program's text is in Korean.

| Screen | Command | Action |
|---|---|---|
| Main | `print` | Goes to the summary screen |
| Main | `new` | Goes to the score entry screen |
| Main | `exit` | Quits |
| Score entry | `new` | Asks for one student's ID, name, Korean score and English score in turn |
| Summary | `id`, `name`, `korean`, `english` | Prints the list sorted by ID, name, Korean score or English score |
| Score entry, Summary | `back` | Returns to the main screen |

| Field | Rule |
|---|---|
| Student ID | An integer from 100 to 999 that is not already registered |
| Name | 1 to 5 lowercase English letters. The first letter is stored capitalized |
| Korean, English score | An integer from 0 to 100 |

Input that breaks a rule is rejected with the reason and asked for again. Up to 256 students can be registered, and the scores are kept in memory while the program runs. After a sort field is chosen on the summary screen, the program asks for the sort direction, which is typed in Korean as `오름차순` (ascending) or `내림차순` (descending). The averages and standard deviations of the Korean and English scores are printed below the table.


## How it works

**Screens are stacked in a line buffer and printed at once.** `MenuManager` uses a 128-line character array as a list of lines, and the first line that starts with a null character marks the end. Every screen change clears it with `menuClear`, stacks lines with `menuAdd`, and `menuPrint` prints them with a left margin. The main loop interprets commands according to the current screen number (`RoomMain`, `RoomPrint`, `RoomNewStudent`), and when the number becomes `none`, `changeMenu` returns `false` and the loop ends.

```c
while (changeMenu(currentMenuIndex, currentMenu))
{
	menuGetCommand(command);
	switch (currentMenuIndex)
	{
		...
	}
	system("cls");
}
```

**Input validation has two layers.** `StringExt` checks whether a string consists only of digits (a leading sign is allowed), only uppercase letters or only lowercase letters. `InputExt` reads a line with `gets_s` and keeps printing an error message and reading again until the check passes. The ranges of the ID and scores and the length of the name are checked once more above that, in `Main.c`. `true`, `false` and `null`, which C lacks, and `none` for an empty value are defined as macros in `Boolean.h` and `Null.h`.

**Sorting swaps four arrays together.** Student data sits in four arrays for ID, name, Korean and English at the same index. A pointer picks the array to sort by (names are compared with `strcmp`), the i-th element is compared with each element after it, and when the order is wrong the two slots are swapped in all four arrays. Integers are swapped with an XOR swap.

**The standard deviation uses a hand-written power function.** A recursive `power` adds up the squared deviations, the sum is divided by the number of students, and `sqrt` takes the square root.


## Files

| Path | Content |
|---|---|
| `source/ClassManager.sln` | Visual Studio 2015 solution |
| `source/ClassManager/Main.c` | Main loop, screen layouts, field input, sorting, average and standard deviation |
| `source/ClassManager/MenuManager.c` | Screen line buffer |
| `source/ClassManager/InputExt.c` | Input functions that ask again until the check passes |
| `source/ClassManager/StringExt.c` | Digit, uppercase and lowercase checks |
| `source/ClassManager/Boolean.h`, `source/ClassManager/Null.h` | Definitions of `true`, `false`, `null` and `none` |
| `docs/screenshots/` | Screenshots |
| Releases | Executable |


## License

zlib. See [LICENSE](LICENSE).

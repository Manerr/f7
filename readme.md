# WIP File Explorer for TI CE Calculators

This is a **work-in-progress** (WIP) file explorer application built for TI CE calculators using the **CE C Compiler Toolchain (CECToolchain)**.

The current builtin one is completely f\*cked up, and is not very usable at all. You don't have search, sorting, or even at least a better UI.


## 🚧 Current Features

- Lists all programs and appvars in the archive and RAM. (More filetypes are coming, the fact is just that you'll have a different interaction with them compared to programs and appvars )
- Displays each file's size in bytes

## 🔧 Built With

- The [CE C Toolchain](https://github.com/CE-Programming/toolchain) – for developing C programs on TI-84+ CE calculators

## 📝 Usage

1. Compile using the CE C Toolchain.
2. Transfer the `.8xp` file to your calculator using TI-Connect CE, and launch artifice | asmhook to run it. [https://yvantt.github.io/arTIfiCE/)(https://yvantt.github.io/arTIfiCE/)

## 📌 Notes

- Not finished , you can only list some of the files and their sizes.
- Planned features may include: file opening, deletion, categorization,searching, and sorting.



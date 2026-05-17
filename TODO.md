# Porting VMS Pascal Moria to Free Pascal — TODO

This document lists all the changes needed to convert the VMS Pascal source
of Moria 4.8 to Free Pascal.  Each item notes a **difficulty** rating:

- **Easy** — mechanical text substitution, no semantic change.
- **Medium** — requires understanding but has a straightforward FPC equivalent.
- **Hard** — requires redesign, significant new code, or platform-specific work.

---

## 1. Build System

**File:** `build.com`
**Difficulty:** Medium

`build.com` is a VMS DCL command procedure.  It needs to be replaced with a
portable build system such as a `Makefile` (or `build.sh`).  The new build
script must compile the Pascal sources with `fpc`, link them, and place the
resulting binary in the `execute/` directory.  The VMS logical-name mechanism
for directory paths (`MOR_INCLUDE:`, `MOR_SOURCE:`, etc.) must also be
replaced with relative filesystem paths.

---

## 2. Program/Module Structure

**Files:** `moria.pas`, `termdef.pas`
**Difficulty:** Medium

### 2a. `[environment(...)]` attribute
```pascal
[environment('moria.env')] program moria(input,output);
```
VMS Pascal uses pre-compiled environment files (`.env`) to share type and
variable declarations across separately compiled modules.  Free Pascal has no
such mechanism.  Remove the `[environment('moria.env')]` attribute; the program
header becomes simply `program moria;`.

### 2b. `[inherit(...)]` / `module` in `termdef.pas`
```pascal
[inherit('moria.env')] module a;
```
VMS Pascal's `module` construct (which inherits a shared environment) has no
Free Pascal equivalent.  `termdef.pas` must be rewritten as a Free Pascal
`unit` (see also item 11, TERMDEF rewrite).

### 2c. `[external] procedure termdef; external;` declaration
The combined `[external]` attribute + `external` keyword is VMS-specific.
In Free Pascal, an external procedure living in a separate unit is referenced
simply by naming the unit in a `uses` clause; no extra declaration is needed.

---

## 3. Include Directives

**Files:** `moria.pas` and all `.inc` files
**Difficulty:** Easy

VMS uses `%INCLUDE` with logical-name paths:
```pascal
%INCLUDE 'MOR_INCLUDE:CONSTANTS.INC'
```
Free Pascal uses compiler directives with relative paths:
```pascal
{$I include/constants.inc}
```
Replace every `%INCLUDE 'MOR_INCLUDE:filename.INC'` with
`{$I include/filename.inc}` (lower-case filenames recommended for
case-sensitive file systems).

---

## 4. Numeric Literals

**Files:** `constants.inc`, `variables.inc`, `values.inc`, and many `.inc` files
**Difficulty:** Easy

| VMS Pascal syntax | Free Pascal syntax | Example |
|---|---|---|
| `%X'1A2B'` (hex) | `$1A2B` | `%X'80000000'` → `$80000000` |
| `%B'0011'` (binary) | `%0011` | `%B'0000000000110000'` → `%0000000000110000` |
| Octal `%O'...'` (none present, but possible) | `&...` | — |

This is a straightforward global search-and-replace.

---

## 5. Type System

**Files:** `types.inc`, `variables.inc`
**Difficulty:** Medium

### 5a. `unsigned` type
VMS Pascal has a built-in `unsigned` (32-bit unsigned integer).
Replace with Free Pascal's `LongWord` (or `Cardinal`).
There are hundreds of uses throughout the code.

### 5b. Storage-size attributes on subrange types
```pascal
byteint  = [byte]  0..255;
bytlint  = [byte]  -128..127;
wordint  = [word]  0..65535;
worlint  = [word]  -32768..32767;
```
The `[byte]` / `[word]` attributes specify the physical storage size.
In Free Pascal use the equivalent built-in types directly:
- `byteint`  → `Byte`
- `bytlint`  → `ShortInt`
- `wordint`  → `Word`
- `worlint`  → `SmallInt`

Update all type aliases (or replace their uses throughout the code).

### 5c. `varying [n] of char` — variable-length strings
VMS Pascal's `varying [n] of char` is a variable-length string with a
maximum of *n* characters and a 16-bit length prefix.  Free Pascal uses
`string[n]` (short string, 1-byte length, max 255) or `AnsiString`.
Because many fields hold strings longer than 255 characters (e.g.,
`ntype = varying[1024] of char` used in `save.inc`), the recommended
replacement is:
- Short strings (max ≤ 255): `string[n]`
- Long strings (max > 255): `AnsiString` (and adjust code accordingly)

The main string type aliases (`atype`, `btype`, `ctype`, `dtype`, `etype`,
`mtype`, `ntype`, `ttype`, `vtype`) defined in `types.inc` need updating.

### 5d. `quad_type` record
```pascal
quad_type = record l0 : unsigned; l1 : unsigned; end;
```
Used exclusively for VMS timer calls (see item 10).  Once the timer calls
are replaced, this type can be removed or replaced with `Int64`.

---

## 6. VMS-Specific Variable Attributes

**File:** `variables.inc`
**Difficulty:** Easy

Every variable declaration has a `[psect(name)]` or `[psect(name),global]`
attribute, e.g.:
```pascal
seed : [psect(player$data),global] unsigned;
```
These attributes control placement in named VMS program sections and global
symbol visibility.  Free Pascal ignores unknown attributes but they are
still syntax errors — remove all `[psect(...)]` and `[global]` attributes.
The `[global]` visibility concern is irrelevant once the code is reorganised
into Free Pascal units.

---

## 7. Bit-Field Record Fields

**Files:** `types.inc` (record types `floor_type`, `cave_type`, `monster_type`)
**Difficulty:** Hard

VMS Pascal supports bit-level field layout using `[bit(n),pos(m)]` attributes:
```pascal
cave_type = record
    cptr  : byteint;
    tptr  : byteint;
    fval  : [bit(4),pos(16)] 0..15;
    fopen : [bit(1),pos(20)] boolean;
    fm    : [bit(1),pos(21)] boolean;
    pl    : [bit(1),pos(22)] boolean;
    tl    : [bit(1),pos(23)] boolean;
end;
```
Free Pascal has no equivalent attribute syntax.  Two options:
- **Option A** (simpler): Expand each packed record into individual fields of
  the smallest suitable type; discard the physical bit layout (it only matters
  for the on-disk save format, which is being redesigned anyway — see item 13).
- **Option B** (preserves layout): Represent the whole record as a `LongWord`
  and use bitwise operations for access; wrap in properties if desired.

Option A is recommended as it makes the code more readable.

---

## 8. Unsigned Integer Bitwise Functions

**Files:** Many `.inc` files
**Difficulty:** Easy

VMS Pascal provides `uor`, `uand`, `uxor`, `uint`, `int` as built-in
functions for unsigned bitwise arithmetic:

| VMS Pascal | Free Pascal replacement |
|---|---|
| `uor(a, b)` | `a or b` (with operands cast to `LongWord`) |
| `uand(a, b)` | `a and b` |
| `uxor(a, b)` | `a xor b` |
| `uint(x)` | `LongWord(x)` |
| `int(x)` | `LongInt(x)` |

These appear in several hundred places.  A global search-and-replace is
feasible, but care is needed where operands are signed integers that must
be treated as unsigned — explicit casts to `LongWord` may be required.

---

## 9. String Operations

**Files:** Many `.inc` files (especially `io.inc`, `misc.inc`, `save.inc`, `desc.inc`, `moria.inc`, `wizard.inc`)
**Difficulty:** Medium

### 9a. `writev` / `readv`
VMS Pascal's `writev` writes formatted output *into a string* (like C's
`sprintf`); `readv` parses values *from a string* (like C's `sscanf`).
Free Pascal replacements:
- `writev(str, ...)` → `WriteStr(str, ...)` (FPC ≥ 2.4) or `str()`/`Format()`
- `readv(str, ...)` → `ReadStr(str, ...)` (FPC ≥ 2.4) or `Val()`

`writev`/`readv` accept the same format-width specifiers as `write`/`read`
(e.g., `:1`, `:2`, `:3:2`), so `WriteStr`/`ReadStr` are the closest
equivalents.  The `error:=continue` error-handling clause (see item 13b)
must also be dropped.

### 9b. `substr(str, pos, len)`
Replace with `Copy(str, pos, len)`.  The semantics are identical.

### 9c. `index(str, pattern)`
VMS Pascal `index(source, pattern)` returns the 1-based position of the
first occurrence of `pattern` in `source`, or 0 if not found.
Free Pascal's `Pos(pattern, source)` does the same but with **arguments in
reverse order**.  Replace every `index(s, p)` with `Pos(p, s)`.

### 9d. `pad(str, fillchar, len)`
VMS Pascal `pad(str, ch, len)` pads `str` to a minimum length of `len` by
appending `ch`.  Free Pascal has no built-in equivalent; implement a small
helper function, e.g.:
```pascal
function Pad(const s: string; ch: Char; len: Integer): string;
begin
  Result := s;
  while Length(Result) < len do Result := Result + ch;
end;
```
This function is called in many places across `io.inc`, `misc.inc`,
`death.inc`, `save.inc`, and `files.inc`.

### 9e. `insert_str` (macro, `insert.mar`)
The `INSERT_STR` VAX MACRO routine searches a varying string for a match
substring and replaces it in-place.  Replace with a Pascal helper function
using `Pos`, `Copy`, and string concatenation.

---

## 10. `case … otherwise` → `case … else`

**Files:** Many `.inc` files
**Difficulty:** Easy

VMS Pascal uses `otherwise` as the default clause of a `case` statement.
Free Pascal uses `else`.  Replace every `otherwise` at the start of a case
arm with `else`.

---

## 11. `value` Section for Global Variable Initialization

**File:** `values.inc`
**Difficulty:** Medium

VMS Pascal allows a `value` section to initialise global variables:
```pascal
value
    death := false;
    used_line := (22 of false);
    bit_array := (%X'00000001', %X'00000002', ...);
```
Free Pascal has no `value` section.  Move initialisations to:
- Typed constants (`const x: T = value;`) for simple scalar values, or
- The `initialization` section of the relevant unit, or
- An explicit `InitVars` procedure called at program start.

The `(N of value)` array replication syntax (e.g., `(22 of false)`) is also
VMS-specific.  Replace with `FillChar` or a loop, e.g.:
```pascal
FillChar(used_line, SizeOf(used_line), 0);
```
Hexadecimal array literals (in `bit_array` and `wdata`) must also have their
`%X'...'` prefixes converted to `$...` (see item 4).

---

## 12. VMS System Calls — Terminal I/O

**Files:** `io.inc`, `termdef.pas`, `putqio.mar`
**Difficulty:** Hard

The entire terminal I/O subsystem uses VMS-specific QIO (Queued I/O):

- `SYS$ASSIGN` — assigns an I/O channel to `TT:`.
- `SYS$QIOW` — performs synchronous queued I/O for both output and keyboard
  input.
- `PUT_BUFFER` / `PUT_QIO` (in `putqio.mar`) — a VAX MACRO assembly buffer
  that accumulates output and flushes it via QIO.
- `TERMDEF` / `SYS$GETDVI` — queries the terminal type and builds cursor-
  addressing escape sequences.
- `LIB$DISABLE_CTRL` / `LIB$ENABLE_CTRL` — disables/re-enables Ctrl-Y.

**Recommended replacement strategy:**

1. Drop `termdef.pas` entirely.  Modern systems are almost universally ANSI/
   VT100 compatible; hard-code ANSI cursor-addressing sequences.
2. Replace `put_buffer` + `put_qio` with a Pascal procedure that writes
   a cursor-positioning sequence followed by the string to `stdout` (or to a
   `ncurses` window).  Consider using the Free Pascal `CRT` unit or the
   `ncurses` binding (`fpc-ncurses` package).
3. Replace `inkey` / `inkey_delay` with `ReadKey` from the `CRT` unit (or
   `ncurses`).  Raw/no-echo mode is handled automatically by `CRT`.
4. Replace `flush` with `CRT`'s implicit flush or an explicit
   `Flush(stdout)`.
5. `no_controly` / `controly` can be replaced with `CRT`'s raw-mode handling,
   or simply removed (Ctrl-C handling via `SigInt` on POSIX is sufficient).

---

## 13. VMS System Calls — Time and Process Info

**Files:** `io.inc`, `misc.inc`, `death.inc`
**Difficulty:** Medium

### 13a. `SYS$GETTIM` / `SYS$BINTIM` / `SYS$SETIMR` / `SYS$WAITFR`
Used in `get_seed` (random seed from clock), `convert_time`, `sleep`, and
`setup_io_pause`.  Replace with Free Pascal/OS equivalents:
- `get_seed`: use `{$I-} Now {$I+}` or `GetTickCount64` to derive a seed, or
  use `SysUtils.GetTime` / `DateTimeToTimeStamp`.
- `sleep(n)`: use `SysUtils.Sleep(n * 1000)` (argument is seconds in original).
- `setup_io_pause`: this pre-computed a timer for a workaround specific to
  VMS 3.x device-driver bugs; it can be removed entirely.

### 13b. `SYS$GETJPI` — process information
Used in two places:
- `get_paths` (`io.inc`): retrieves the path of the running image to locate
  data files.  Replace with `ParamStr(0)` (the executable path) and
  `ExtractFilePath` from `SysUtils`.
- `get_username` (`death.inc`): retrieves the VMS username for the high-score
  table.  Replace with `GetEnvironmentVariable('USER')` on POSIX, or
  `GetEnvironmentVariable('USERNAME')` on Windows.

### 13c. `LIB$GET_FOREIGN` — command-line argument
Used to retrieve the optional `/WIZARD` command-line flag passed to the
program when invoked from DCL.  Replace with `ParamStr` / `FindCmdLineSwitch`
from `SysUtils`, or simply inspect `ParamStr(1)`.

### 13d. `LIB$DAY` — day of week; `time()` — current time string
- `LIB$DAY` → `DayOfWeek` from `SysUtils`.
- `time(time_str)` (VMS runtime call returning a packed time string) →
  `GetTime` from `SysUtils` or `FormatDateTime`.

### 13e. `SYS$SETPRV` — privilege manipulation
The `priv_switch` procedure enables/disables the SYSPRV privilege so that
the game can read/write system-area files when installed as a privileged
image.  This concept has no equivalent on other platforms.  Replace
`priv_switch(0)` and `priv_switch(1)` calls with no-ops; the file permission
model on POSIX/Windows replaces it.

### 13f. `SYS$EXIT` / `LIB$SPAWN`
- `SYS$EXIT` → `Halt` (Free Pascal built-in).
- `LIB$SPAWN` (shell escape in `io.inc`) → `fpSystem` (unit `BaseUnix`) or
  `SysUtils.ExecuteProcess`.

### 13g. `OTS$CVT_TZ_L` — hex string to integer
Used in `get_hex_value` (wizard mode).  Replace with
`StrToInt('$' + hexstring)` from `SysUtils`.

---

## 14. External Procedure / Function Declarations

**Files:** `io.inc`, `misc.inc`, `death.inc`, and others
**Difficulty:** Easy (once the called routines are replaced)

VMS Pascal declares external routines with a combined attribute and keyword:
```pascal
[asynchronous,external(SYS$QIOW)] function qiow_read(...) : integer;
    external;
```
The attributes `[asynchronous]`, `[external(name)]`, and the parameter
modifiers `%immed`, `%ref`, `%stdescr`, `%descr` are all VMS-specific.
Once the VMS system calls are replaced (items 12–13) these entire
declarations are removed.

For the macro-assembly routines (`randint`, `distance`, etc.) the `external`
declarations are replaced by Pascal implementations (see item 16).

---

## 15. File I/O

**Files:** `files.inc`, `save.inc`, `death.inc`
**Difficulty:** Hard

VMS Pascal extends standard Pascal file I/O significantly:

### 15a. Extended `open` / `close` syntax
```pascal
open(f, file_name:=MORIA_HOU, history:=readonly, sharing:=readonly,
     error:=continue);
```
Free Pascal uses `Assign(f, name)` followed by `Reset(f)` or `Rewrite(f)`.
The VMS-specific keyword parameters (`file_name:=`, `history:=`, `sharing:=`,
`organization:=`, `access_method:=`, `record_length:=`, `disposition:=`) must
be removed; their semantics are handled differently (see below).

The `error:=continue` clause suppresses VMS runtime errors; replace with
`{$I-}` compiler directive + `IOResult` checks, or with `try`/`except`.

### 15b. `status(file)` function
VMS Pascal's `status(f)` returns 0 on success and an error code otherwise
(tested immediately after `open` or `rewrite`).  Replace with `IOResult`
(after `{$I-}`) for file operations.

### 15c. Keyed/indexed file organisation (ISAM)
The high-score file (`MORIACHR.DAT` / `MORIA_MAS`) and character save master
file use VMS RMS indexed-sequential files with a key field:
```pascal
file2 : file of key_type;
open(file2, ..., access_method:=keyed, organization:=indexed, ...);
```
```pascal
key_type = record
    file_id : [key(0)] packed array [1..70] of char;
    seed    : integer;
end;
```
Free Pascal has no built-in ISAM support.  Options:
- Rewrite using a plain sequential text file (simplest, breaks backward
  compatibility with saved characters).
- Use a simple binary file with a linear scan for lookup.
- Use an embedded database (e.g., SQLite via the `sqlite3` binding).

The `[key(0)]` record attribute must be removed regardless.

### 15d. `history:=old` / `history:=new` / `history:=readonly`
These map roughly to:
- `history:=old` → file must exist → `Reset`
- `history:=new` → create new → `Rewrite`
- `history:=readonly` → open for reading → `Reset`

### 15e. `disposition:=delete`
Used in `save.inc` to auto-delete the file on close.  Replace with explicit
`DeleteFile(filename)` after `Close(f)`.

### 15f. `write(file1, ..., error:=continue)` / `readln(file, line, error:=continue)`
The `error:=` clause is VMS-specific.  Remove it; handle errors via
`IOResult` or exceptions.

---

## 16. VAX MACRO Assembly Routines

**Directory:** `source/macro/`
**Difficulty:** Medium (all eight routines are small and well-documented)

All eight `.MAR` files are VAX MACRO assembly and must be replaced with
Pascal implementations:

| File | Function | Replacement |
|---|---|---|
| `randint.mar` | `randint(maxval)` — uniform PRNG, 1..maxval | Implement LCG directly in Pascal using the same multiplier (16807) and modulus (2147483647); or use Free Pascal's `Random` after seeding with `RandSeed`. |
| `randrep.mar` | `rand_rep(num, die)` — sum of `num` rolls of `die` | Simple loop calling `randint`. |
| `distance.mar` | `distance(y1,x1,y2,x2)` — integer distance approx. | Three-line Pascal function using `Abs` and arithmetic. |
| `bitpos.mar` | `bit_pos(var x)` — index of lowest set bit, clears it | Use `BSF` intrinsic or bit-scan loop in Pascal. |
| `insert.mar` | `insert_str(src, match, replace)` — string replacement | See item 9e. |
| `maxmin.mar` | `maxmin(x,y,z)` = `max(min(x,y)-1, z)` | One-liner in Pascal. |
| `minmax.mar` | `minmax(x,y,z)` — presumably `min(max(x,y)+1, z)` | One-liner in Pascal. |
| `putqio.mar` | `put_buffer` / `put_qio` — output buffer + QIO flush | Replace with the new terminal I/O layer (item 12). |

The global variable `seed` (used by `randint` and `randrep`) must become a
regular Pascal variable visible to the replacement functions; in the VMS
version it was a global symbol accessed directly from assembler.

---

## 17. Calling-Convention Parameter Modifiers

**Files:** `io.inc`, `misc.inc`, and all files declaring `external` routines
**Difficulty:** Easy (removed as part of item 14)

VMS Pascal supports several parameter-passing modifiers that are meaningless
in Free Pascal:

| Modifier | Meaning | Action |
|---|---|---|
| `%immed` | pass by immediate value | remove |
| `%ref` | pass by reference | remove (use `var` if needed) |
| `%stdescr` | pass as string descriptor | remove |
| `%descr` | pass as descriptor | remove |
| `[unsafe]` | suppress type-checking | remove |
| `[volatile]` | mark as volatile | remove |

These appear only on parameters of `external` (VMS system call) routines.
Once those routines are replaced (items 12–14), the modifiers disappear
along with their declarations.

---

## 18. `[psect(...)]` Psect Attributes on Procedures

**Files:** All `.inc` files
**Difficulty:** Easy

Many procedure/function definitions carry a `[psect(name$code)]` attribute
that places the routine's code in a named VMS program section:
```pascal
[psect(io$code)] procedure inkey(var getchar : char);
```
Free Pascal ignores unknown attributes but they are syntax errors.
Remove all `[psect(...)]` attributes from procedure/function definitions.

---

## 19. The `$` Character in Identifiers

**Files:** `constants.inc`, `variables.inc`, `values.inc`
**Difficulty:** Easy

VMS Pascal allows `$` in identifiers (e.g., `io$bin_pause`, `player$data`,
`store$choices`).  Free Pascal does not.  Rename all such identifiers,
replacing `$` with `_` (e.g., `io_bin_pause`, `store_choices`).

---

## 20. `set of 0..255` — Large Set Types

**File:** `types.inc`
**Difficulty:** Easy

```pascal
obj_set = set of 0..255;
```
Free Pascal supports `set of Byte` (equivalent to `set of 0..255`) natively.
This should work as-is after the type replacements in item 5, but note that
Free Pascal sets of more than 32 elements are stored as bit arrays and may
have slightly different performance characteristics.  No code changes needed.

---

## 21. Octal Literals in `values.inc`

**File:** `values.inc`
**Difficulty:** Easy

The `wdata` array initialiser contains octal literals written without the
VMS `%O` prefix (just bare numbers with leading zeros), e.g.:
```pascal
wdata := (
    (011065, 87, 36, ...),
    ...);
```
In VMS Pascal bare leading-zero integers are still decimal.  In Free Pascal
the same is true, so this part is fine.  However, verify during testing that
the encryption/password logic still works correctly after type changes.

---

## 22. Operating-Hours System

**Files:** `files.inc`, `misc.inc`
**Difficulty:** Medium

The game reads `HOURS.DAT` to decide whether it is "open" for play.  This is
a multi-user timesharing feature from the original VMS deployment.  For a
personal Free Pascal port:
- Either keep the feature (the file format is simple text and requires no VMS
  specifics once file I/O is ported).
- Or remove the check entirely, which simplifies `intro()` considerably.

---

## 23. Help System (`moriahlp.hlb`)

**File:** `execute/moriahlp.hlb`; `help.inc`
**Difficulty:** Medium

The help file is a VMS HLB (Help Library) binary file, and the help
procedure calls the VMS librarian system (`LBR$` routines) implicitly
through the VMS HELP facility.  In `help.inc`, check how help is accessed
and replace with a plain text file reader or a hard-coded help screen.

---

## Summary Table

| # | Area | Difficulty |
|---|---|---|
| 1 | Build system (replace `build.com`) | Medium |
| 2 | Program/module structure | Medium |
| 3 | `%INCLUDE` → `{$I}` | Easy |
| 4 | Numeric literal prefixes (`%X`, `%B`) | Easy |
| 5 | Type system (`unsigned`, `varying`, storage attributes) | Medium |
| 6 | `[psect]` / `[global]` variable attributes | Easy |
| 7 | Bit-field record layout attributes | Hard |
| 8 | Unsigned bitwise functions (`uor`, `uand`, `uxor`, …) | Easy |
| 9 | String operations (`writev`, `readv`, `substr`, `index`, `pad`) | Medium |
| 10 | `otherwise` → `else` in `case` statements | Easy |
| 11 | `value` section / array replication `(N of x)` | Medium |
| 12 | VMS terminal I/O (QIO, TERMDEF, `putqio.mar`) | Hard |
| 13 | VMS system calls (time, process info, privileges, …) | Medium |
| 14 | External VMS procedure declarations | Easy |
| 15 | File I/O (VMS `open` extensions, ISAM indexed files) | Hard |
| 16 | VAX MACRO assembly routines (8 files) | Medium |
| 17 | VMS parameter modifiers (`%immed`, `%ref`, …) | Easy |
| 18 | `[psect]` attributes on procedures | Easy |
| 19 | `$` in identifiers | Easy |
| 20 | `set of 0..255` | Easy |
| 21 | Octal literals in `values.inc` | Easy |
| 22 | Operating-hours system | Medium |
| 23 | VMS Help Library | Medium |

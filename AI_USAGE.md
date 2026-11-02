# AI\_USAGE.md

**Tool/model and date:** Claude, 10/27/2026

**Purpose:**
I used Claude as a learning assistant while completing Task 3, to understand the security rationale behind each compiler/linker hardening option before adding it to the build command, and to confirm I understood why checksec reported the results it did on both binaries.

**What I used:**

I used AI assistance to:

* Confirm that the minimal fix for the overflow was a bounds check before the `memcpy`, not a larger buffer or a different compiler flag.
* Understand the practical difference between `-fstack-protector`, `-fstack-protector-strong`, and `-fstack-protector-all`, and why `-strong` was the appropriate choice here.
* Understand what `-fPIE -pie` and Full RELRO (`-z,relro,-z,now`) each protect against, and why the vulnerable binary showed "No PIE" / "Partial RELRO" while the fixed binary showed "PIE enabled" / "Full RELRO."
* Confirm that `-Wall -Wextra -Werror` catches unrelated compiler warnings rather than the missing-bounds-check logic bug itself.

**What I changed:**

I wrote and compiled the actual fix and the hardened build command myself, then compared the explanations against my own checksec output for both binaries. Where my initial report draft stated FORTIFY as simply "yes" without explaining the partial count, I added the explanation of why only some calls get fortified, based on this. I did not copy any code or flag combinations directly from the AI responses without first checking them against the assignment's specified build command.

**How I tested it:**

I rebuilt both `legacy\_log\_parser` and `legacy\_log\_parser\_fixed` with the exact flags in the assignment, ran `checksec --file=` on each, and compared the RELRO, Stack Canary, NX, PIE, and FORTIFY fields against what the AI explanations predicted. I also re-ran all five Task 3 test cases (short input, maximum valid input, one byte over, missing file, original exploit payload) against the fixed binary to confirm the bounds check, not just the compiler flags, was what rejected the oversized and exploit inputs.

**One error, limitation, or rejected suggestion:**

An early AI suggestion proposed increasing `BUF\_SIZE` instead of adding a bounds check, which would not have fixed the underlying vulnerability (it just raises the threshold at which the same unchecked copy overflows). I rejected that suggestion and instead added the explicit `n >= BUF\_SIZE` check before the `memcpy`, keeping the original 128-byte buffer as specified in the assignment.

**AI Logs:**

https://claude.ai/share/ecfdfcfa-cb17-43d4-928a-75bb1e7ca85d


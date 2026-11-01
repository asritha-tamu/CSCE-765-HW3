# CSCE 465/765 – HW3: From Prompt to Process

## Project Overview

This project explores the security risks of a vulnerable log parser, indirect prompt injection against an AI agent, compiler-based security protections, and operating-system access control using AppArmor.

## Requirements

- Ubuntu 24.04
- GCC
- GDB
- checksec
- Python 3
- AppArmor

## Project Structure

- `src/` – Vulnerable and hardened C parser source files and payload generator.
- `tests/` – Test inputs, exploit payload, and test results.
- `skills/legacy-parser/` – Agent skill instructions and secure wrapper.
- `web/` – Adversarial webpage used for the prompt-injection scenario.
- `policy/` – AppArmor security profile.
- `markers/` – Marker files created by the ret2win demonstration.
- `inbox/` – Permitted parser input files.

## Task 1 – Vulnerable Parser

Build the original parser:

```bash
gcc -O0 -g -fno-stack-protector -no-pie \
-Wl,-z,noexecstack -Wall -Wextra \
-o legacy_log_parser src/legacy_log_parser.c
```

Generate the exploit payload:

```bash
python3 src/make_payload.py
```

Run the demonstration:

```bash
./legacy_log_parser tests/payload.bin
```

The payload overwrites the saved return address and redirects execution to `win()`.

## Task 2 – Agent Skill and Prompt Injection

Inspect the skill:

```bash
cat skills/legacy-parser/SKILL.md
```

Test an allowed path:

```bash
skills/legacy-parser/run_parser.sh inbox/short.log
```

Test a rejected path:

```bash
skills/legacy-parser/run_parser.sh tests/short.log
```

The OpenClaw agent execution was attempted but did not complete because of an LLM network connection error. See `tests/task2_results.txt`.

## Task 3 – Hardened Parser

Build the fixed parser:

```bash
gcc -O2 -g -fstack-protector-strong -D_FORTIFY_SOURCE=3 \
-fPIE -pie -Wl,-z,relro,-z,now -Wl,-z,noexecstack \
-Wall -Wextra -Werror \
-o legacy_log_parser_fixed src/legacy_log_parser_fixed.c
```

Run all tests:

```bash
./tests/test_parser.sh
```

The test script checks short input, maximum-size input, oversized input, missing files, and the original exploit payload.

## Task 4 – AppArmor Confinement

The AppArmor profile is located at:

```text
policy/apparmor.profile
```

Load or update it with:

```bash
sudo apparmor_parser -r policy/apparmor.profile
```

Check its status:

```bash
sudo aa-status
```

The parser was tested under the `agentlab` account with restricted file and program access.

## Security Analysis

See `tests/task4_security_explanation.txt` for the Task 4 discussion of reference monitors, complete mediation, access matrices, DAC, MAC, and least privilege.

## Evidence

Screenshots and test outputs document the experiments. See the report for the results and limitations of each task.


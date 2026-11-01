# AI Usage Disclosure 

## AI Tool and Model Used

- Tool: OpenAI ChatGPT (GPT-6)
- Additional tool: OpenClaw connected to the TAMUS AI API (`protected.gpt-4o`)
- Dates: October 29–30, 2026

## Purpose

AI tools were used for learning support, debugging assistance, code review, test planning, understanding security concepts, and documentation.

## How AI Was Used

ChatGPT was used throughout the assignment to help understand the buffer overflow vulnerability, interpret GDB output, and understand how the vulnerable parser's stack layout affected the return address.

AI assistance was also used to:

- Understand the purpose of the vulnerable and hardened C parser implementations.
- Develop and troubleshoot the Python exploit-payload generation approach.
- Understand compiler hardening options, including stack canaries, PIE, RELRO, NX, and FORTIFY_SOURCE.
- Develop test cases for normal, maximum-size, oversized, missing-file, and exploit-payload inputs.
- Understand AppArmor confinement, file permissions, access restrictions, and denial logs.
- Review the agent skill instructions and explain the indirect prompt-injection scenario.
- Prepare shell commands, test documentation, README content, and the security analysis.

OpenClaw connected to the TAMUS AI API and was used to test the adversarial webpage scenario. The successful agent response recognized the embedded indirect prompt injection and declined to invoke the legacy-parser skill.

## AI Conversation Log Files

- `AI_CONVERSATION_LOG.md` – Contains selected prompts and relevant AI responses covering implementation, debugging, testing, and documentation across the four tasks.

## Validation and Human Involvement

Commands and code were executed and tested in the Ubuntu VirtualBox environment. GDB output, parser behavior, checksec results, test results, and AppArmor behavior were reviewed to verify the implementation.

AI-generated suggestions were treated as assistance rather than automatically accepted results. Technical claims were checked against the experiments performed in the local environment.

## Limitations

The initial OpenClaw agent execution failed because of an LLM network connection error. After restoring the TAMU compatibility shim, the connection was successful. The agent then successfully read the adversarial webpage, identified the embedded prompt injection, and declined to invoke the legacy-parser skill.
## Responsibility

We reviewed and tested the implementation and are responsible for the submitted code, configurations, experiments, and explanations. Both team members are responsible for understanding the entire assignment and its results.

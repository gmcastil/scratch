#!/bin/bash

# A common feature of Bash scripts is to determine if they are being source or run
# as a command.  To determine this, the canonical way to do it is through the
# following:

if [[ "${BASH_SOURCE[0]}" == "${0}" ]]; then
    printf '%s\n' "Script was executed"
fi

if [[ "${BASH_SOURCE[0]}" != "${0}" ]]; then
    printf '%s\n' "Script was sourced"
fi


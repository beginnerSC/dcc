#!/bin/bash

if [[ "$1" == "-h" || "$1" == "--help" || "$1" == "/?" ]]; then
    echo "Usage: reset.sh [target|all]"
    echo ""
    echo "Examples:"
    echo "  reset.sh vector"
    echo "  reset.sh all"
    echo ""
    echo "Default target is vector when omitted."
    exit 0
fi

DCC_ROOT="$(dirname "$(realpath "$0")")"
DCC_TARGET="${1:-vector}"

poetry run python -c "import os, sys; from pathlib import Path; root = Path(os.environ['DCC_ROOT']).resolve(); sys.path.insert(0, str(root / 'src')); from dcc import reset_targets; target = os.environ['DCC_TARGET']; results = reset_targets([target], project_root=root); print('Reset complete:', ', '.join(results.keys()))"

if [ $? -ne 0 ]; then
    echo "Reset failed."
    exit 1
fi

echo "Done."
exit 0
from __future__ import annotations

from collections.abc import Iterable
from pathlib import Path


def _resolve_project_root(project_root: str | Path | None = None) -> Path:
    return Path(project_root).resolve() if project_root else Path(__file__).resolve().parents[2]


def _get_target_paths(target: str, project_root: Path) -> tuple[Path, Path]:
    normalized_target = target.strip().lower()
    if not normalized_target:
        raise ValueError("Target cannot be empty")

    header_path = project_root / "cpp" / "include" / "dcc_core" / f"{normalized_target}.h"
    source_path = project_root / "cpp" / "src" / f"{normalized_target}.cpp"
    return header_path, source_path


def list_resettable_targets(project_root: str | Path | None = None) -> list[str]:
    root = _resolve_project_root(project_root)
    headers_dir = root / "cpp" / "include" / "dcc_core"
    sources_dir = root / "cpp" / "src"

    if not headers_dir.exists() or not sources_dir.exists():
        return []

    header_targets = {path.stem.lower() for path in headers_dir.glob("*.h")}
    source_targets = {path.stem.lower() for path in sources_dir.glob("*.cpp")}

    return sorted(header_targets & source_targets)


def reset_target(
    target: str = "vector",
    project_root: str | Path | None = None,
) -> tuple[Path, Path]:
    root = _resolve_project_root(project_root)

    header_path, source_path = _get_target_paths(target, root)

    for path in (header_path, source_path):
        if not path.exists():
            raise FileNotFoundError(f"File not found: {path}")
        path.write_text("", encoding="utf-8")

    return header_path, source_path


def reset_targets(
    targets: Iterable[str] | None = None,
    project_root: str | Path | None = None,
) -> dict[str, tuple[Path, Path]]:
    root = _resolve_project_root(project_root)
    target_list = [target.strip().lower() for target in targets] if targets else ["vector"]

    if len(target_list) == 1 and target_list[0] == "all":
        target_list = list_resettable_targets(root)
        if not target_list:
            raise FileNotFoundError("No resettable targets found")

    results: dict[str, tuple[Path, Path]] = {}
    for target in target_list:
        results[target] = reset_target(target=target, project_root=root)

    return results
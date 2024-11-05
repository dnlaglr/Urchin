#!/bin/bash

OPSYS="$(uname -s)"
BINDIR="/usr/local/bin"
URCHINBIN="$BINDIR/urchinCLI"

removeFromPath() {
  SHELLCONFIG="$HOME/.bashrc"
  [[ "$SHELL" == *zsh ]] && SHELLCONFIG="$HOME/.zshrc"

  if grep -q "export PATH=\$PATH:$BINDIR" "$SHELLCONFIG"; then
    sed -i.bak "/export PATH=\\\$PATH:$BINDIR/d" "$SHELLCONFIG"
    echo "Removed $BINDIR from PATH in $SHELLCONFIG. Restart your shell or run \`source $SHELLCONFIG\` to apply changes."
  fi
}

if [[ "$OPSYS" == "Linux" && -f /etc/arch-release ]]; then
  echo "Detected Arch Linux."

  if [[ -f "$URCHINBIN" ]]; then
    sudo rm -f "$URCHINBIN"
    echo "Urchin binary removed from $BINDIR."
  else
    echo "Urchin binary not found in $BINDIR."
  fi
  removeFromPath

elif [[ "$OPSYS" == "Darwin" ]]; then
  echo "Detected MacOS."

  if [[ -f "$URCHINBIN" ]]; then
    sudo rm -f "$URCHINBIN"
    echo "Urchin binary removed from $BINDIR."
  else
    echo "Urchin binary not found in $BINDIR."
  fi
  removeFromPath

else
  echo "$OPSYS is currently unsupported by this uninstall script!"
  exit 1
fi

echo "Uninstallation complete! Urchin has been removed."

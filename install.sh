#!/bin/bash

OPSYS="$(uname -s)"
BINDIR="/usr/local/bin"
URCHINBIN="urchin/bin/urchinCLI"

addToPath() {
  SHELLCONFIG="$HOME/.bashrc"
  [[ "$SHELL" == *zsh ]] && SHELLCONFIG="$HOME/.zshrc"

  if ! grep -q "$BINDIR" "$SHELLCONFIG"; then
    echo "export PATH=\$PATH:$BINDIR" >> "$SHELLCONFIG"
    echo "Updated PATH in $SHELLCONFIG. Restart your shell or run `source $SHELLCONFIG` to run Urchin from any directory."
  fi
}

if [[ "$OPSYS" == "Linux" && -f /etc/arch-release ]]; then
  echo "Detected Arch Linux."

  sudo mkdir -p "$BINDIR"

  sudo cp "$URCHINBIN" "$BINDIR/urchin"
  sudo chmod +x "$BINDIR/urchin"
  echo "Urchin installed in $BINDIR."
  addToPath

elif [[ "$OPSYS" == "Darwin" ]]; then
  echo "Detected MacOS."

  sudo mkdir -p "$BINDIR"

  sudo cp "$URCHINBIN" "$BINDIR/urchin"
  sudo chmod +x "$BINDIR/urchin"
  echo "Urchin installed in $BINDIR."
  addToPath

else
  echo "$OPSYS is currently unsupported! Consider adding support for Urchin at 'https://github.com/dnlaglr/Urchin'!"
  exit 1
fi

echo "Installation complete! You can now run 'urchin <command>' from any directory!"

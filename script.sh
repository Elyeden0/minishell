#!/bin/bash

# Répertoire courant = racine du projet
SEARCH_DIR="$PWD"

echo "Analyse de la racine du projet : $SEARCH_DIR"
echo "-------------------------------------------"

# Fonction utilitaire pour compter les fonctions dans un ensemble de fichiers
# Arguments :
#   $1 : description (pour l'affichage)
#   ${@:2} : paramètres passés à find (chemin(s) + filtres)
count_functions() {
  local label="$1"; shift

  # On récupère tous les .c correspondant aux critères find, puis on greppe dessus
  local matches
  matches=$(find "$@" -type f -name '*.c' -print0 \
            | xargs -0 grep -Phzo \
              '((static\s+)?[a-zA-Z_][a-zA-Z0-9_\s\*]*\s+[a-zA-Z_][a-zA-Z0-9_]*\s*\([^\)]*\))\s*\n?\s*\{' \
            2>/dev/null)

  local total=$(echo "$matches" | grep -c '{')
  local static=$(echo "$matches" | grep -c 'static')
  local normal=$(( total - static ))

  echo "$label"
  echo "  ├─ Total   : $total"
  echo "  ├─ Normales: $normal"
  echo "  └─ Static  : $static"
  echo
}

# 1) Analyse récursive hors dossier lib
count_functions "Fonctions hors lib :" \
  "$SEARCH_DIR" -not -path "$SEARCH_DIR/lib/*"

# 2) Analyse **seulement total** dans le dossier lib
if [ -d "$SEARCH_DIR/lib" ]; then
  lib_total=$(find "$SEARCH_DIR/lib" -type f -name '*.c' -print0 \
                | xargs -0 grep -Phzo \
                  '((static\s+)?[a-zA-Z_][a-zA-Z0-9_\s\*]*\s+[a-zA-Z_][a-zA-Z0-9_]*\s*\([^\)]*\))\s*\n?\s*\{' \
                2>/dev/null | grep -c '{')
  echo "Fonctions dans lib :"
  echo "  └─ Total : $lib_total"
else
  echo "Le dossier lib n'existe pas, analyse lib ignorée."
fi

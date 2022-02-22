#!/bin/bash
echo "Update lineups : "
python3 Scrap_nba_lineups.py
echo "Done"
echo "Copying to GitHup Repo :"
cp NBA_lineups* ../HotPicks/
echo "Done"
cd ../HotPicks/
git add .
git commit -m "update"
#git push
git push https://Aldros50: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@github.com/Aldros50/HotPicks.git --all
echo "Done"

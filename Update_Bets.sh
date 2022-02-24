#!/bin/bash
echo "Updating standing : "
python3 Scrap_nba_standing.py
echo "Done"
echo "Update lineups : "
python3 Scrap_nba_lineups.py
echo "Done"
echo "Updating Schedule : "
python3 Scrap_nba_schedule.py 2022 02 24
echo "Done"
echo "Updating Game Id Collections : "
root -l -q 'NBA_Update_GameId_Collection.cxx(2022,02,24)'
echo "Done"
echo "Scraping Last Games : "
python3 Scrap_nba.py 20220223
echo "Done"
#echo "Remove old bets :"
#rm -rf bets/*.csv
#echo "Done"
echo "Updating bets info from Winamax : "
python3 Scrap_winamax_nba.py
echo "Update Completed"
echo "Updating bets info from Draftking : "
python3 Scrap_draftking.py
echo "Update Completed"
echo "Updating Player Stats :"
root -l -q NBA_Data_To_Json.cxx
echo "Done"
echo "Update Schedule :"
root -l -q 'NBA_Schedule_To_Json.cxx(2022,02,24)'
echo "Done"
echo "Copying to GitHup Repo :"
cp *.html ../HotPicks/
echo "Done"
cd ../HotPicks/
#git add .
#git commit -m "update"
#git push
#git push https://Aldros50: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@github.com/Aldros50/HotPicks.git --all
echo "Done"

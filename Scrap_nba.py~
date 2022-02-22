# Import libraries
import requests
import urllib.request
import time
from bs4 import BeautifulSoup
import csv
import sys

def scrap_nba(date):

    #Get GameId of the day from schedule
    GameId = []
    with open('/local/home/ar245054/AndroidAssests/HotPicks/macros/NBA_Data/2021_2022/schedule/Schedule_'+str(date)+'.csv', newline='') as csvfile:
        spamreader = csv.reader(csvfile, delimiter=',', quotechar='|')
        for row in spamreader:
            if row[2]!='Id':
                GameId.append(row[2])
                #print(row)

    print('Nbr of Games Found : ')
    print(len(GameId))
    print(GameId)

    #Loop over IDs
    for y in range(0,len(GameId)):

        x = GameId[y]
        
        # Set the URL you want to webscrape from
        url = 'https://www.espn.com/nba/boxscore?gameId='+str(x)
        print(url)

        # Connect to the URL
        response = requests.get(url)

        # Parse HTML and save to BeautifulSoup object
        soup = BeautifulSoup(response.text, "html.parser")

        # create and write headers to a list 
        rows = []
        rowsH = []
        rows.append(['Name','MIN','FG','3PT','FT','OREB','DREB','REB','AST','STL','BLK','TO','PF','PTS','PorM'])
        rowsH.append(['Name','MIN','FG','3PT','FT','OREB','DREB','REB','AST','STL','BLK','TO','PF','PTS','PorM'])
    
        #find team names
        tableNA = soup.find('div', attrs={'class': 'team away'})
        resultsNA = tableNA.find_all('span')
        tableNH = soup.find('div', attrs={'class': 'team home'})
        resultsNH = tableNH.find_all('span')
        teamName = []
        teamName.append([resultsNA[2].getText(),resultsNH[2].getText(),2])
        teamA = []
        teamA.append([resultsNA[2].getText()])
        teamH = []
        teamH.append([resultsNH[2].getText()])
    
        #print('Number of results', len(resultsN))

        #find results within table
        table = soup.find('div', attrs={'class': 'col column-one gamepackage-away-wrap'})
        results = table.find_all('tr')
        #print('Number of results', len(results))
    
        # loop over results
        for result in results:
            # find all columns per result
            data = result.find_all('td')
            # check that columns have data 
            if len(data) != 15: 
                continue
    
            # write columns to variables
            Name = data[0].getText()
            MIN = data[1].getText()
            FG = data[2].getText()
            ThreePT = data[3].getText()
            FT = data[4].getText()
            OREB = data[5].getText()
            DREB = data[6].getText()
            REB = data[7].getText()
            AST = data[8].getText()
            STL = data[9].getText()
            BLK = data[10].getText()
            TO = data[11].getText()
            PF = data[12].getText()
            PorM = data[13].getText()
            PTS = data[14].getText()

            if Name != 'TEAM':
                if MIN != '':
                    #print(Name)
                    # write each result to rows
                    rows.append([Name,MIN,FG,ThreePT,FT,OREB,DREB,REB,AST,STL,BLK,TO,PF,PTS,PorM])

        #find results within table
        tableh = soup.find('div', attrs={'class': 'col column-two gamepackage-home-wrap'})
        resultsh = tableh.find_all('tr')
        #length.append([len(resultsh)])
        #print('Number of results', len(resultsh))

        # loop over results
        for result in resultsh:
            # find all columns per result
            data = result.find_all('td')
            # check that columns have data 
            if len(data) != 15: 
                continue
    
            # write columns to variables
            Name = data[0].getText()
            MIN = data[1].getText()
            FG = data[2].getText()
            ThreePT = data[3].getText()
            FT = data[4].getText()
            OREB = data[5].getText()
            DREB = data[6].getText()
            REB = data[7].getText()
            AST = data[8].getText()
            STL = data[9].getText()
            BLK = data[10].getText()
            TO = data[11].getText()
            PF = data[12].getText()
            PorM = data[13].getText()
            PTS = data[14].getText()

            if Name != 'TEAM':
                if MIN != '':
                    # write each result to rows
                    rowsH.append([Name,MIN,FG,ThreePT,FT,OREB,DREB,REB,AST,STL,BLK,TO,PF,PTS,PorM])


    
        #print(rows)

        # Create csv and write rows to output file
        fileN = 'NBA_Data/2021_2022/NBA_ID_'+str(x)+'.csv'
        with open(fileN,'w', newline='') as f_output:
            csv_output = csv.writer(f_output)
            csv_output.writerows(teamName)
            csv_output.writerows(teamA)
            csv_output.writerows(rows)
            csv_output.writerows(teamH)
            csv_output.writerows(rowsH)
    

if __name__ == "__main__":
    date = int(sys.argv[1])
    scrap_nba(date)


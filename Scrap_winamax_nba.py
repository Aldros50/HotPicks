# Import libraries
import requests
import urllib.request
import time
import json
from selenium import webdriver
import selenium
from bs4 import BeautifulSoup
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.action_chains import ActionChains
import csv

#to get the games url
urlmain = 'https://www.winamax.fr/paris-sportifs/sports/2/15/177'

print(urlmain)

d = webdriver.Chrome("/local/home/ar245054/AndroidAssests/HotPicks/OLD_STUFF/Scrapper/chromedriver")

d.get(urlmain)

# Connect to the URL
pageSourcemain = d.page_source

# Parse HTML and save to BeautifulSoup object
soupmain = BeautifulSoup(pageSourcemain, "html.parser")


tableurl = soupmain.find_all('a', attrs={"class": "sc-dlfnbm bcaJjD sc-gbkRTH fblxkw"},href=True)

url = []

for a in tableurl:
    url.append('https://www.winamax.fr'+a['href'])
    print("Found the URL: ", 'https://www.winamax.fr'+a['href'])

d.quit()

for a in url:

    print(a)
    
    d = webdriver.Chrome("/local/home/ar245054/AndroidAssests/HotPicks/OLD_STUFF/Scrapper/chromedriver")
    
    d.get(a)

    #total_height = int(d.execute_script("return document.body.scrollHeight"))

    #for i in range(1, total_height, 5):
    #    d.execute_script("window.scrollTo(0, {});".format(i))
    #    time.sleep(1)
        
    #input('Done clicking:')
    
    #y = 1000
    #for timer in range(0,5):
    #     d.execute_script("window.scrollTo(0, "+str(y)+")")
    #     y += 1000  
    #     time.sleep(10)
    
    #scroll down
    #d.execute_script("window.scrollTo(0, document.body.scrollHeight);")

    #WebDriverWait(d, 1000)

    # Connect to the URL
    pageSourcemain = d.page_source
    
    # Parse HTML and save to BeautifulSoup object
    soupmain = BeautifulSoup(pageSourcemain, "html.parser")
    

    #betbox = soupmain.find('div', attrs={"class": "sc-vewwy kiISKu"})
    #betbox = soupmain.find('div', attrs={"class": "sc-JJYMh edkAQS"})
    betbox = soupmain.find('div', attrs={"id": "inner-wrap"})

    box = betbox.find_all('div', attrs={"class": "sc-vewwy kiISKu"})

    row_teamH = []
    row_teamA = []
    TeamN = []

    #row_teamH.append(['Player','Stat','Val','0.'])
    #row_teamA.append(['Player','Stat','Val','0.'])

    #Get Team Names
    boxname = soupmain.find_all('div', attrs={"class": "sc-erkbxa kVUyez sc-jEUCeg dzhKAn"})
    #print(len(boxname))
    if len(boxname) == 1:
        teams = boxname[0].find_all('span')
        #print(len(teams))
        if len(teams)==3:
            TeamN.append(teams[0].getText())
            TeamN.append(teams[2].getText())
            #print(teams[0].getText())
            #print(teams[1].getText())
            
    for b in box:
        boxname = b.find_all('div', attrs={"class": "sc-ieGSVO fGIfUh"})
        #print(boxname[0].text)
        #print('Number of boxes : ',len(boxname))
        if len(boxname) == 1:
            player = b.find_all('div', attrs={"class": "sc-fUSoCb cTIAGG label-text"})
            bets = b.find_all('div', attrs={"class": "sc-clQlwS icIOwD"})
            if boxname[0].text == "Nombre de rebonds du joueur?":
                print("BOX : ", boxname[0].text)
                print("Bets Found : ",len(bets))
                print("Players Found : ",len(player))
                if len(player)*2 == len(bets):
                    for x in range(0,len(player)):
                        #print(bets[2*x].getText())
                        #print(player[x].getText())
                        StrPlayer = player[x].getText()
                        Name = StrPlayer.split(' (')[0]
                        First = Name.split(' ')[0]
                        Last = Name.split(' ')[1]
                        Name = First[0]+'. '+Last
                        Team = StrPlayer.split(' (')[1]
                        Team = Team.split(')')[0]
                        StrBets = bets[2*x].getText()
                        Value = StrBets.split('Plus de ')[1]
                        Value = Value.split(',')[0]
                        Value = Value+'.5'
                        #print(Name)
                        #print(Team)
                        #print(Value)
                        if Team == TeamN[0]:
                            row_teamH.append([Name,'REB',Value,'0.'])
                        if Team == TeamN[1]:
                            row_teamA.append([Name,'REB',Value,'0.'])
                            
            if boxname[0].text == "Nombre de passes décisives du joueur?":
                print("BOX : ", boxname[0].text)
                print("Bets Found : ",len(bets))
                print("Players Found : ",len(player))
                if len(player)*2 == len(bets):
                    for x in range(0,len(player)):
                        #print(bets[2*x].getText())
                        #print(player[x].getText())
                        StrPlayer = player[x].getText()
                        Name = StrPlayer.split(' (')[0]
                        First = Name.split(' ')[0]
                        Last = Name.split(' ')[1]
                        Name = First[0]+'. '+Last
                        Team = StrPlayer.split(' (')[1]
                        Team = Team.split(')')[0]
                        StrBets = bets[2*x].getText()
                        Value = StrBets.split('Plus de ')[1]
                        Value = Value.split(',')[0]
                        Value = Value+'.5'
                        #print(Name)
                        #print(Team)
                        #print(Value)
                        if Team == TeamN[0]:
                            row_teamH.append([Name,'AST',Value,'0.'])
                        if Team == TeamN[1]:
                            row_teamA.append([Name,'AST',Value,'0.'])

            if boxname[0].text == "Nombre de paniers à 3 points du joueur?":
                print("BOX : ", boxname[0].text)
                print("Bets Found : ",len(bets))
                print("Players Found : ",len(player))
                if len(player)*2 == len(bets):
                    for x in range(0,len(player)):
                        #print(bets[2*x].getText())
                        #print(player[x].getText())
                        StrPlayer = player[x].getText()
                        Name = StrPlayer.split(' (')[0]
                        First = Name.split(' ')[0]
                        Last = Name.split(' ')[1]
                        Name = First[0]+'. '+Last
                        Team = StrPlayer.split(' (')[1]
                        Team = Team.split(')')[0]
                        StrBets = bets[2*x].getText()
                        Value = StrBets.split('Plus de ')[1]
                        Value = Value.split(',')[0]
                        Value = Value+'.5'
                        #print(Name)
                        #print(Team)
                        #print(Value)
                        if Team == TeamN[0]:
                            row_teamH.append([Name,'3PM',Value,'0.'])
                        if Team == TeamN[1]:
                            row_teamA.append([Name,'3PM',Value,'0.'])

    #Generate File Name
    Name_Short = "FAIL"
    #print(len(TeamN))
    if len(TeamN) > 0:
        for x in range(0,2):
            Team = []
            Team = TeamN[x].split(' ')
            #print(len(Team))
            Name = Team[len(Team)-1]
            print(Name)
            if Name=="Hawks": Name_Short="ATL"
            if Name=="Nets": Name_Short="BKN"
            if Name=="Celtics": Name_Short="BOS"
            if Name=="Hornets": Name_Short="CHA"
            if Name=="Bulls": Name_Short="CHI"
            if Name=="Cavaliers": Name_Short="CLE"
            if Name=="Mavericks": Name_Short="DAL"
            if Name=="Nuggets": Name_Short="DEN"
            if Name=="Pistons": Name_Short="DET"
            if Name=="Warriors": Name_Short="GS"
            if Name=="Rockets": Name_Short="HOU"
            if Name=="Pacers": Name_Short="IND"
            if Name=="Clippers": Name_Short="LAC"
            if Name=="Lakers": Name_Short="LAL"
            if Name=="Grizzlies": Name_Short="MEM"
            if Name=="Heat": Name_Short="MIA"
            if Name=="Bucks": Name_Short="MIL"
            if Name=="Timberwolves": Name_Short="MIN"
            if Name=="Pelicans": Name_Short="NO"
            if Name=="Knicks": Name_Short="NY"
            if Name=="Thunder": Name_Short="OKC"
            if Name=="Magic": Name_Short="ORL"
            if Name=="76ers": Name_Short="PHI"
            if Name=="Suns": Name_Short="PHX"
            if Name=="Blazers": Name_Short="POR"
            if Name=="Spurs": Name_Short="SA"
            if Name=="Kings": Name_Short="SAC"
            if Name=="Raptors": Name_Short="TOR"  
            if Name=="Jazz": Name_Short="UTAH"
            if Name=="Wizards": Name_Short="WSH"
          
            # Create csv and write rows to output file
            fileN = 'bets/winamax_'+Name_Short+'.csv'
            with open(fileN,'w', newline='') as f_output:
                csv_output = csv.writer(f_output)
                if x==0:
                    csv_output.writerows(row_teamH)
                if x==1:
                    csv_output.writerows(row_teamA)
    d.quit()

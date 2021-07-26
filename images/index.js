const Web3 = require("web3");
var ethers = require("ethers");
const EthDater = require('ethereum-block-by-date');
var Contract = require("web3-eth-contract");
const fs = require("fs");
const fetch = require("node-fetch");

Contract.setProvider("wss://mainnet.infura.io/ws/v3/349d968855af4703970f5a4a66919f1a");

const web3 = new Web3(new Web3.providers.WebsocketProvider('wss://mainnet.infura.io/ws/v3/349d968855af4703970f5a4a66919f1a'));
const dater = new EthDater(
    web3
);

var creamEthStartBlock = 10590000;
var curDate = Date.now() - 300000;
console.log("current date is " + curDate);

var ethRatesFinal = [];
var bscRatesFinal = {};
var ethBlockArr = [];

var existingJson = [];
var ethRatesObj = {};

var newBlocksToCheck = [];
var oldEthRatesJsonFile = [];

async function retrieveBlocks(){
    console.log("Hello");
    const result = await dater.getEvery(
        "days",
        "2020-08-05T00:00:00Z",
        curDate,
        1,
        true
    );
    ethBlockArr = result;
    console.log(result);
    fs.writeFileSync("examp1.json", JSON.stringify(ethBlockArr));
    retrieveRates();
}

async function retrieveNewBlocks(){
    let pastDates = [];
    if (fs.existsSync("ethrates.json")) {
        var rawdata = fs.readFileSync("ethrates.json");
        var parseddata = JSON.parse(rawdata);
        pastDates = parseddata;
    }
    else {
        process.exit(22);
    }

    oldEthRatesJsonFile = pastDates;
    let mostRecentDate = pastDates[pastDates.length - 1][0];
    const blocksToCheck = await dater.getEvery(
        "days",
        mostRecentDate,
        curDate,
        1,
        true
    );
    blocksToCheck.shift();
    if (blocksToCheck.length == 0) {
        console.log("Nothing new to add, exiting.");
        process.exit(22);
    }
    newBlocksToCheck = blocksToCheck;
    ethBlockArr = blocksToCheck;
    console.log("Amount of new blocks to check: " + ethBlockArr.length);
    retrieveRates();
}



/*let ethblocks = await dater.getEvery(
    "days",
    "2020-08-04T00:00:00Z",
    (Date.now() - 300000),
    1,
    true
);*/

function exitFunc(){
    fs.writeFileSync("ethrates.json", JSON.stringify(ethRatesFinal));
    process.exit(22);
}

function updateFunc(){
    const updatedArray = oldEthRatesJsonFile.concat(ethRatesFinal);
    console.log("WRITING NOW");
    fs.writeFileSync("ethrates.json", JSON.stringify(updatedArray));
    process.exit(22);
}

async function retrieveRates() {
    console.log("Retrieving rates");
    let curiter = 0;
    let iterstarted = 0;
    let iterdone = 0;
    console.log("ethRatesFinal length is: " + ethRatesFinal.length);
    while (ethRatesFinal.length < ethBlockArr.length) {

        curiter = curiter + 1;
        iterstarted = iterstarted + 1;
        let currblock = ethBlockArr[iterdone];
        let currblocknum = "" + currblock["block"];
        let currblockdate = currblock["date"];
        let currentRequestUrl = "https://api.cream.finance/api/v1/rates?block_number=" + currblocknum + "&comptroller=eth";
        console.log(currentRequestUrl);

        await fetch(currentRequestUrl)
            .then(async function (result) {
                    console.log("FETCHING");
                    //console.log(result.json());
                    //var currresp = result.text();

                    //console.log("11111111111111 Json text is: " + currresp);
                    //var realresp = JSON.parse(currresp);
                    await result.json().then(function (data) {

                            var newadd = [currblockdate, data];
                            console.log("RESULT IS --------------- " + data + "################ END OF RESULT");
                            console.log("################# New add is: ############: " + newadd);
                            ethRatesFinal.push(newadd);
                            iterdone = iterdone + 1;
                            //fs.writeFileSync("ethrates.json", JSON.stringify(ethRatesFinal));
                            console.log("ethratesfinal length is: " + ethRatesFinal.length);
                            console.log("ethBlockArr length is: " + ethBlockArr.length);
                            if (ethRatesFinal.length == ethBlockArr.length) {
                                //exitFunc();
                                updateFunc();
                            }
                        }
                    )
                    //var newadd = [currblockdate, realresp];

                    //console.log("RESULT IS --------------- " + result + "################ END OF RESULT");
                    //ethRatesFinal.push(newadd);
                    //fs.writeFileSync("ethrates.json", JSON.stringify(ethRatesFinal));

                }
            )
    }
}

function readJsons() {
    if (fs.existsSync("ethrates.json")) {
        var rawdata = fs.readFileSync("ethrates.json");
        var parseddata = JSON.parse(rawdata);
        existingJson = parseddata;
    }
}

function traverseEveryDate(){
    for (i = 0; i < existingJson.length; i++) {
        let currentPair = existingJson[i];
        let currentTraversedDate = currentPair[0];
        let currentRateInfo = currentPair[1];
        console.log("Current date: " + currentTraversedDate);
        let curDateRates = handleDate(currentTraversedDate, currentRateInfo);

        for (var property in curDateRates) {
            let curDouble = curDateRates[property];
            let curTriple = [currentTraversedDate, curDouble[0], curDouble[1]];
            if (property in ethRatesObj) {
                let oldPropValue = ethRatesObj[property];
                oldPropValue.push(curTriple);
                ethRatesObj[property] = oldPropValue;
            }
            else {
                ethRatesObj[property] = [curTriple];
            }
        }
    }
}

function handleDate(givenDate, givenObj) {
    let tokenObj = {};
    let givenObjLend = givenObj["lendRates"];
    let givenObjBorrow = givenObj["borrowRates"];

    for (j = 0; j < givenObjLend.length; j++) {
        let listObjLend = givenObjLend[j];
        let listObjBorrow = givenObjBorrow[j];
        let curTokenName = listObjLend.tokenSymbol;
        let curTokenLendRate = listObjLend.apy;
        let curTokenBorrowRate = listObjBorrow.apy;
        tokenObj[curTokenName] = [curTokenLendRate, curTokenBorrowRate];
    }

    return tokenObj;
}

function writeEthJson(){
    fs.writeFileSync("ethTokensRates.json", JSON.stringify(ethRatesObj));
    process.exit(22);
}




/*
//retrieveBlocks();
readJsons();
traverseEveryDate();
writeEthJson();
*/


//update ethrates with this function.
//retrieveNewBlocks();

//after updating ethrates, update ethTokensRates with these three functions
readJsons();
traverseEveryDate();
writeEthJson();
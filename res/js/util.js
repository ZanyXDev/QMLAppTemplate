.pragma library

const QMLAppType = {
    "Zero": 0,
    "One": 1
}



function getRandomBackGround() {
    var bgrStr = Math.floor(Math.random() * 20 + 1).toString()
    if (bgrStr.length === 1) {
        bgrStr = "0" + bgrStr
    }
    return "qrc:/res/images/backgrounds/bgr" + bgrStr + ".jpg"
}

function getNextBgrImage(index) {
    var bgrStr
    if ((index === undefined) || (index > 20) || (index < 0)) {
        index = 0
    }
    if (index < 10) {
        bgrStr = "0" + index
    } else {
        bgrStr = index
    }

    return "qrc:/res/images/backgrounds/bgr" + bgrStr + ".jpg"
}

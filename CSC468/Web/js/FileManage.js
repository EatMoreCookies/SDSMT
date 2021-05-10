function readCookies(cookies){
    let list = [];
    let index = -1;

    for( let i = 0; i < 5; ++i){
        index = cookies.search(cookiesVars[i])
        if(  index !== -1)
            list.push( cookies[index+5])
        else
            list.push(0);
    }
    return list;
}

function Load(filename){
    let rawFile = new XMLHttpRequest();

    rawFile.open("GET", "https://dev.cse.sdsmt.edu/~7416949/uploads/" + filename, false);
    rawFile.send();

    if(rawFile.status === 200)
    {
        let allText = rawFile.responseText;
        let list = allText.split("\n");
        document.cookie = "head=" + list[0];
        document.cookie = "larm=" + list[1];
        document.cookie = "body=" + list[2];
        document.cookie = "rarm=" + list[3];
        document.cookie = "legs=" + list[4];

        window.location.href = "https://dev.cse.sdsmt.edu/~7416949/index.php";
    }

    else
        alert("Failed to load file");
}

function Save(){
        window.location.href = "https://dev.cse.sdsmt.edu/~7416949/index.php?save=1";
}

function Delete(filename){
    window.location.href = "https://dev.cse.sdsmt.edu/~7416949/FileManagement.php?delete=" + filename;
}

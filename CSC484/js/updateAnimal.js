function showDogForm() {
    document.getElementById('cat-selector').classList.remove('selected')
    document.getElementById('dog-selector').classList.add('selected')
    document.getElementById('rabbit-selector').classList.remove('selected')
    document.getElementById("dog-form").classList.remove("hide");
    document.getElementById("cat-form").classList.add("hide");
    document.getElementById("rabbit-form").classList.add("hide");
    document.getElementById("formSelectedIndicator").value = "1"
}

function showCatForm() {
    document.getElementById('cat-selector').classList.add('selected')
    document.getElementById('dog-selector').classList.remove('selected')
    document.getElementById('rabbit-selector').classList.remove('selected')
    document.getElementById("dog-form").classList.add("hide");
    document.getElementById("cat-form").classList.remove("hide");
    document.getElementById("rabbit-form").classList.add("hide");
    document.getElementById("formSelectedIndicator").value = "0"
}

function showRabbitForm() {
    document.getElementById('cat-selector').classList.remove('selected')
    document.getElementById('dog-selector').classList.remove('selected')
    document.getElementById('rabbit-selector').classList.add('selected')
    document.getElementById("dog-form").classList.add("hide");
    document.getElementById("cat-form").classList.add("hide");
    document.getElementById("rabbit-form").classList.remove("hide");
    document.getElementById("formSelectedIndicator").value = "2"
}

document.getElementById("cat-selector").addEventListener("click", showCatForm)
document.getElementById("dog-selector").addEventListener("click", showDogForm)
document.getElementById("rabbit-selector").addEventListener("click", showRabbitForm)
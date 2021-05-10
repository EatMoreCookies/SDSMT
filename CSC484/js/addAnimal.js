function displayCatForm() {
    document.getElementById("pet-color").classList.remove("hide");
    document.getElementById("species-input").value = "0"
    document.getElementById('cat-selector').classList.add('selected')
    document.getElementById('dog-selector').classList.remove('selected')
    document.getElementById('rabbit-selector').classList.remove('selected')
}

function displayDogForm() {
    document.getElementById("pet-color").classList.add("hide");
    document.getElementById("species-input").value = "1"
    document.getElementById('cat-selector').classList.remove('selected')
    document.getElementById('dog-selector').classList.add('selected')
    document.getElementById('rabbit-selector').classList.remove('selected')
}

function displayRabbitForm() {
    document.getElementById('cat-selector').classList.remove('selected')
    document.getElementById('dog-selector').classList.remove('selected')
    document.getElementById('rabbit-selector').classList.add('selected')
    document.getElementById("pet-color").classList.add("hide");
    document.getElementById("species-input").value = "2"
}

document.getElementById("cat-selector").addEventListener("click", displayCatForm)
document.getElementById("dog-selector").addEventListener("click", displayDogForm)
document.getElementById("rabbit-selector").addEventListener("click", displayRabbitForm)
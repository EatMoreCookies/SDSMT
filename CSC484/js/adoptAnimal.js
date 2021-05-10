function displayCats() {
    document.getElementById('cat-selector').classList.add('selected')
    document.getElementById('dog-selector').classList.remove('selected')
    document.getElementById('rabbit-selector').classList.remove('selected')
    document.getElementById('cat-display').classList.remove("hide")
    document.getElementById('dog-display').classList.add("hide")
    document.getElementById('rabbit-display').classList.add("hide")
    document.getElementById('species-input').value = "Cat"
}

function displayDogs() {
    document.getElementById('cat-selector').classList.remove('selected')
    document.getElementById('dog-selector').classList.add('selected')
    document.getElementById('rabbit-selector').classList.remove('selected')
    document.getElementById('cat-display').classList.add("hide")
    document.getElementById('dog-display').classList.remove("hide")
    document.getElementById('rabbit-display').classList.add("hide")
    document.getElementById('species-input').value = "Dog"
}

function displayRabbits() {
    document.getElementById('cat-selector').classList.remove('selected')
    document.getElementById('dog-selector').classList.remove('selected')
    document.getElementById('rabbit-selector').classList.add('selected')
    document.getElementById('cat-display').classList.add("hide")
    document.getElementById('dog-display').classList.add("hide")
    document.getElementById('rabbit-display').classList.remove("hide")
    document.getElementById('species-input').value = "Rabbit"
}

document.getElementById("cat-selector").addEventListener("click", displayCats)
document.getElementById("dog-selector").addEventListener("click", displayDogs)
document.getElementById("rabbit-selector").addEventListener("click", displayRabbits)
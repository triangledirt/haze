class trfTask {
    var id: Int
    var resources = [Bool]()
    var duration: Double

    init(id: Int, resourceMap: [Bool], expectedDuration: Double) {
        self.id = id;
        resources = resourceMap
        duration = expectedDuration
    }
}

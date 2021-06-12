import XCTest
@testable import trf

final class trfTests: XCTestCase {
    func testTask() {
        let sync = trfSync()
	let taskCount = 64
        for _ in 0..<taskCount {
            var resources = [Bool]()
	    let resourceCount = 64
            for i in 0..<resourceCount {
                resources[i] = Bool.random()
            }
            let taskID = Int.random(in: 0..<1000000)
            var duration = Double.random(in: 0.0..<1.0)
            var task = trfTask(id: taskID,
	                       resourceMap: resources,
	                       expectedDuration: duration)
            sync.addTask(task: task)
        }
        var batches = sync.synchronize()
	for batch in batches {
	    for task in batch {
    	        print("\(task.id)")
            }
	    print("")
	}
    }

    func testExample() {
        // This is an example of a functional test case.
        // Use XCTAssert and related functions to verify your tests produce
        // the correct results.
        XCTAssertEqual(trf().text, "Hello, World!")
    }

    static var allTests = [
      ("testExample", testExample),
      ("testTask", testTask),
    ]
}

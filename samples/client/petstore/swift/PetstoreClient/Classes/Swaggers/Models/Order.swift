//
// Order.swift
//
// Generated by swagger-codegen
// https://github.com/swagger-api/swagger-codegen
//

import Foundation


class Order: JSONEncodable {

    enum Status: String { 
        case Placed = "placed"
        case Approved = "approved"
        case Delivered = "delivered"
    }
    
    var id: Int?
    var petId: Int?
    var quantity: Int?
    var shipDate: NSDate?
    /** Order Status */
    var status: Status?
    var complete: Bool?
    

    // MARK: JSONEncodable
    func encodeToJSON() -> AnyObject {
        var nillableDictionary = [String:AnyObject?]()
        nillableDictionary["id"] = self.id
        nillableDictionary["petId"] = self.petId
        nillableDictionary["quantity"] = self.quantity
        nillableDictionary["shipDate"] = self.shipDate?.encodeToJSON()
        nillableDictionary["status"] = self.status?.rawValue
        nillableDictionary["complete"] = self.complete
        let dictionary: [String:AnyObject] = APIHelper.rejectNil(nillableDictionary) ?? [:]
        return dictionary
    }
}

/* 
 * Swagger Petstore
 *
 * This spec is mainly for testing Petstore server and contains fake endpoints, models. Please do not use this for any other purpose. Special characters: \" \\
 *
 * OpenAPI spec version: 1.0.0
 * Contact: apiteam@swagger.io
 * Generated by: https://github.com/swagger-api/swagger-codegen.git
 */

using System;
using System.Linq;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Runtime.Serialization;
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using PropertyChanged;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;

namespace IO.Swagger.Model
{
    /// <summary>
    /// ArrayTest
    /// </summary>
    [DataContract]
    [ImplementPropertyChanged]
    public partial class ArrayTest :  IEquatable<ArrayTest>, IValidatableObject
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="ArrayTest" /> class.
        /// </summary>
        /// <param name="ArrayOfString">ArrayOfString.</param>
        /// <param name="ArrayArrayOfInteger">ArrayArrayOfInteger.</param>
        /// <param name="ArrayArrayOfModel">ArrayArrayOfModel.</param>
        public ArrayTest(List<string> ArrayOfString = null, List<List<long?>> ArrayArrayOfInteger = null, List<List<ReadOnlyFirst>> ArrayArrayOfModel = null)
        {
            this.ArrayOfString = ArrayOfString;
            this.ArrayArrayOfInteger = ArrayArrayOfInteger;
            this.ArrayArrayOfModel = ArrayArrayOfModel;
        }
        
        /// <summary>
        /// Gets or Sets ArrayOfString
        /// </summary>
        [DataMember(Name="array_of_string", EmitDefaultValue=false)]
        public List<string> ArrayOfString { get; set; }
        /// <summary>
        /// Gets or Sets ArrayArrayOfInteger
        /// </summary>
        [DataMember(Name="array_array_of_integer", EmitDefaultValue=false)]
        public List<List<long?>> ArrayArrayOfInteger { get; set; }
        /// <summary>
        /// Gets or Sets ArrayArrayOfModel
        /// </summary>
        [DataMember(Name="array_array_of_model", EmitDefaultValue=false)]
        public List<List<ReadOnlyFirst>> ArrayArrayOfModel { get; set; }
        /// <summary>
        /// Returns the string presentation of the object
        /// </summary>
        /// <returns>String presentation of the object</returns>
        public override string ToString()
        {
            var sb = new StringBuilder();
            sb.Append("class ArrayTest {\n");
            sb.Append("  ArrayOfString: ").Append(ArrayOfString).Append("\n");
            sb.Append("  ArrayArrayOfInteger: ").Append(ArrayArrayOfInteger).Append("\n");
            sb.Append("  ArrayArrayOfModel: ").Append(ArrayArrayOfModel).Append("\n");
            sb.Append("}\n");
            return sb.ToString();
        }
  
        /// <summary>
        /// Returns the JSON string presentation of the object
        /// </summary>
        /// <returns>JSON string presentation of the object</returns>
        public string ToJson()
        {
            return JsonConvert.SerializeObject(this, Formatting.Indented);
        }

        /// <summary>
        /// Returns true if objects are equal
        /// </summary>
        /// <param name="obj">Object to be compared</param>
        /// <returns>Boolean</returns>
        public override bool Equals(object obj)
        {
            // credit: http://stackoverflow.com/a/10454552/677735
            return this.Equals(obj as ArrayTest);
        }

        /// <summary>
        /// Returns true if ArrayTest instances are equal
        /// </summary>
        /// <param name="other">Instance of ArrayTest to be compared</param>
        /// <returns>Boolean</returns>
        public bool Equals(ArrayTest other)
        {
            // credit: http://stackoverflow.com/a/10454552/677735
            if (other == null)
                return false;

            return 
                (
                    this.ArrayOfString == other.ArrayOfString ||
                    this.ArrayOfString != null &&
                    this.ArrayOfString.SequenceEqual(other.ArrayOfString)
                ) && 
                (
                    this.ArrayArrayOfInteger == other.ArrayArrayOfInteger ||
                    this.ArrayArrayOfInteger != null &&
                    this.ArrayArrayOfInteger.SequenceEqual(other.ArrayArrayOfInteger)
                ) && 
                (
                    this.ArrayArrayOfModel == other.ArrayArrayOfModel ||
                    this.ArrayArrayOfModel != null &&
                    this.ArrayArrayOfModel.SequenceEqual(other.ArrayArrayOfModel)
                );
        }

        /// <summary>
        /// Gets the hash code
        /// </summary>
        /// <returns>Hash code</returns>
        public override int GetHashCode()
        {
            // credit: http://stackoverflow.com/a/263416/677735
            unchecked // Overflow is fine, just wrap
            {
                int hash = 41;
                // Suitable nullity checks etc, of course :)
                if (this.ArrayOfString != null)
                    hash = hash * 59 + this.ArrayOfString.GetHashCode();
                if (this.ArrayArrayOfInteger != null)
                    hash = hash * 59 + this.ArrayArrayOfInteger.GetHashCode();
                if (this.ArrayArrayOfModel != null)
                    hash = hash * 59 + this.ArrayArrayOfModel.GetHashCode();
                return hash;
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        public virtual void OnPropertyChanged(string propertyName)
        {
            // NOTE: property changed is handled via "code weaving" using Fody.
            // Properties with setters are modified at compile time to notify of changes.
            var propertyChanged = PropertyChanged;
            if (propertyChanged != null)
            {
                propertyChanged(this, new PropertyChangedEventArgs(propertyName));
            }
        }

        public IEnumerable<ValidationResult> Validate(ValidationContext validationContext)
        { 
            yield break;
        }
    }

}
